#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_eth_driver.h"
#include "esp_check.h"
#include "esp_mac.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"

#include "driver/gpio.h"
#include "driver/twai.h"

#define TAG             "GENERAL"
#define ETH_TAG         "ETH"
#define WIFI_TAG        "WIFI"
#define TWAI_TAG        "TWAI"
#define MQTT_TAG        "MQTT"

#define VERBOSE_LOG      0

#define ETHERNET_CONFIG  1
#define WIFI_CONFIG      0

#define STATIC_IP        1

/* WIFI Configuration */
#if WIFI_CONFIG
    #define WIFI_SSID      "Zoz"
    #define WIFI_PASS      "Zelmoghazy111"

    static int s_retry_num = 0;
    #define MAXIMUM_RETRY  20

    static EventGroupHandle_t s_wifi_event_group;

    #define WIFI_CONNECTED_BIT BIT0
    #define WIFI_FAIL_BIT      BIT1
#endif  /* WIFI_CONFIG */

/* Ethernet Configuration */
#if ETHERNET_CONFIG
    #define ETH_PHY_ADDR         1
    #define ETH_PHY_RST_GPIO    -1          // not connected
    #define ETH_MDC_GPIO        23
    #define ETH_MDIO_GPIO       18

    static EventGroupHandle_t s_eth_event_group;

    #define ETHERNET_CONNECTED_BIT BIT0
    #define ETHERNET_FAIL_BIT      BIT1
#endif /* ETHERNET_CONFIG */

#if STATIC_IP
    #define S_IP        "192.168.1.5"     
    #define GATEWAY     "192.168.1.1"    
    #define NETMASK     "255.255.255.0"
#endif /* STATIC_IP */

/* MQTT Configuration */
#define MQTT_HOST  "mqtt://192.168.1.100:1883"

/* CAN Configuration */
#define RX_TASK_PRIO            8
#define TX_TASK_PRIO            9
#define ALERT_TSK_PRIO          7

#define TX_GPIO_NUM             5
#define RX_GPIO_NUM             4

#define ID_CTRL                 0x0A0
#define ID_RATE                 0x0EF

#define ID_CTRL_THROTTLE        0x0A1

#define BUFFER_SIZE             256

static const twai_timing_config_t  t_config  = TWAI_TIMING_CONFIG_1MBITS();
static const twai_filter_config_t  f_config  = TWAI_FILTER_CONFIG_ACCEPT_ALL();
/* 
static const twai_filter_config_t f_config = {
    .acceptance_code = (MSG_ID << 21),
    .acceptance_mask = ~(TWAI_STD_ID_MASK << 21),
    .single_filter = true
};
*/
static const twai_general_config_t g_config  = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);

static QueueHandle_t frame_queue_tx;


esp_mqtt_client_handle_t client;

/* Type Definitions */

// Reduce floating point numbers to their individual bytes
union conv32
{
    float    f32; 
    struct{
        uint8_t u8_1;
        uint8_t u8_2;
        uint8_t u8_3;
        uint8_t u8_4;
    }bytes;
};


typedef struct 
{
    union conv32 throttle;
    union conv32 steering;
    uint32_t canid;
}mqtt_message;


static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

/* Clamp data between two values */
static inline double clamp(double d, double min, double max) 
{
  const double t = d < min ? min : d;
  return t > max ? max : t;
}

static inline void parse_double(const char *str, mqtt_message *mqtt) 
{
    char *ptr = NULL;
    mqtt->throttle.f32 = (float)clamp(strtod(str, &ptr),-10.0,10.0);   
    mqtt->steering.f32 = (float)clamp(strtod(ptr, NULL),-28.0,28.0);
}

void app_log(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);
}

#if WIFI_CONFIG
static void wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) 
    {
        esp_wifi_connect();
    } 
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) 
    {
        if (s_retry_num < MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(WIFI_TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(WIFI_TAG,"connect to the AP fail");
    } 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) 
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(WIFI_TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    
    /* Disable Power Saving */
    esp_wifi_set_ps(WIFI_PS_NONE);
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(WIFI_TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     ** number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) 
     */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
                                           WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, 
     ** hence we can test which event actually happened. 
     */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(WIFI_TAG, "connected to ap SSID:%s password:%s",
                 WIFI_SSID, WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(WIFI_TAG, "Failed to connect to SSID:%s, password:%s",
                 WIFI_SSID, WIFI_PASS);
    } else {
        ESP_LOGE(WIFI_TAG, "UNEXPECTED EVENT");
    }
}

#endif /* WIFI_CONFIG */

#if ETHERNET_CONFIG
static esp_eth_handle_t eth_init_internal(esp_eth_mac_t **mac_out, esp_eth_phy_t **phy_out)
{
    esp_eth_handle_t ret = NULL;

    // Init common MAC and PHY configs to default
    eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
    eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();

    // Update PHY config based on board specific configuration
    phy_config.phy_addr = ETH_PHY_ADDR;
    phy_config.reset_gpio_num = ETH_PHY_RST_GPIO;
    // Init vendor specific MAC config to default
    eth_esp32_emac_config_t esp32_emac_config = ETH_ESP32_EMAC_DEFAULT_CONFIG();
    // Update vendor specific MAC config based on board configuration
    esp32_emac_config.smi_mdc_gpio_num = ETH_MDC_GPIO;
    esp32_emac_config.smi_mdio_gpio_num = ETH_MDIO_GPIO;
    // Create new ESP32 Ethernet MAC instance
    esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&esp32_emac_config, &mac_config);
    // Create new PHY instance based on board configuration
    esp_eth_phy_t *phy = esp_eth_phy_new_lan87xx(&phy_config);
    // Init Ethernet driver to default and install it
    esp_eth_handle_t eth_handle = NULL;
    esp_eth_config_t config = ETH_DEFAULT_CONFIG(mac, phy);
    ESP_GOTO_ON_FALSE(esp_eth_driver_install(&config, &eth_handle) == ESP_OK, NULL,
                        err, ETH_TAG, "Ethernet driver install failed");

    if (mac_out != NULL) {
        *mac_out = mac;
    }
    if (phy_out != NULL) {
        *phy_out = phy;
    }
    return eth_handle;
err:
    if (eth_handle != NULL) {
        esp_eth_driver_uninstall(eth_handle);
    }
    if (mac != NULL) {
        mac->del(mac);
    }
    if (phy != NULL) {
        phy->del(phy);
    }
    return ret;
}

esp_err_t example_eth_init(esp_eth_handle_t *eth_handles_out[], uint8_t *eth_cnt_out)
{
    esp_err_t ret = ESP_OK;
    esp_eth_handle_t *eth_handles = NULL;
    uint8_t eth_cnt = 0;

    ESP_GOTO_ON_FALSE(eth_handles_out != NULL && eth_cnt_out != NULL, ESP_ERR_INVALID_ARG,
                        err, ETH_TAG, "invalid arguments: initialized handles array or number of interfaces");
    eth_handles = calloc(1, sizeof(esp_eth_handle_t));
    ESP_GOTO_ON_FALSE(eth_handles != NULL, ESP_ERR_NO_MEM, err, ETH_TAG, "no memory");

    eth_handles[eth_cnt] = eth_init_internal(NULL, NULL);
    ESP_GOTO_ON_FALSE(eth_handles[eth_cnt], ESP_FAIL, err, ETH_TAG, "internal Ethernet init failed");
    eth_cnt++;

    ESP_LOGD(ETH_TAG, "no Ethernet device selected to init");
    *eth_handles_out = eth_handles;
    *eth_cnt_out = eth_cnt;

    return ret;
err:
    free(eth_handles);
    return ret;
}

/** Event handler for Ethernet events */
static void eth_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    uint8_t mac_addr[6] = {0};
    /* we can get the ethernet driver handle from event data */
    esp_eth_handle_t eth_handle = *(esp_eth_handle_t *)event_data;

    switch (event_id) {
    case ETHERNET_EVENT_CONNECTED:
        esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, mac_addr);
        ESP_LOGI(ETH_TAG, "Ethernet Link Up");
        ESP_LOGI(ETH_TAG, "Ethernet HW Addr %02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        break;
    case ETHERNET_EVENT_DISCONNECTED:
        ESP_LOGI(ETH_TAG, "Ethernet Link Down");
        xEventGroupSetBits(s_eth_event_group, ETHERNET_FAIL_BIT);
        break;
    case ETHERNET_EVENT_START:
        ESP_LOGI(ETH_TAG, "Ethernet Started");
        break;
    case ETHERNET_EVENT_STOP:
        ESP_LOGI(ETH_TAG, "Ethernet Stopped");
        break;
    default:
        break;
    }
}

/** Event handler for IP_EVENT_ETH_GOT_IP */
static void got_ip_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
    const esp_netif_ip_info_t *ip_info = &event->ip_info;

    ESP_LOGI(ETH_TAG, "Ethernet Got IP Address");
    ESP_LOGI(ETH_TAG, "~~~~~~~~~~~");
    ESP_LOGI(ETH_TAG, "ETHIP:" IPSTR, IP2STR(&ip_info->ip));
    ESP_LOGI(ETH_TAG, "ETHMASK:" IPSTR, IP2STR(&ip_info->netmask));
    ESP_LOGI(ETH_TAG, "ETHGW:" IPSTR, IP2STR(&ip_info->gw));
    ESP_LOGI(ETH_TAG, "~~~~~~~~~~~");

    xEventGroupSetBits(s_eth_event_group, ETHERNET_CONNECTED_BIT);

}

void ethernet_setup(void)
{
    s_eth_event_group = xEventGroupCreate();
    // Initialize Ethernet driver
    uint8_t eth_port_cnt = 0;
    esp_eth_handle_t *eth_handles;
    ESP_ERROR_CHECK(example_eth_init(&eth_handles, &eth_port_cnt));

    // Initialize TCP/IP network interface aka the esp-netif (should be called only once in application)
    ESP_ERROR_CHECK(esp_netif_init());
    // Create default event loop that running in background
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Create instance(s) of esp-netif for Ethernet(s)
    // Use ESP_NETIF_DEFAULT_ETH when just one Ethernet interface is used and you don't need to modify
    // default esp-netif configuration parameters.
    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_ETH();
    esp_netif_t *eth_netif = esp_netif_new(&cfg);
    
    #if STATIC_IP
        if (esp_netif_dhcpc_stop(eth_netif) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to stop dhcp client");
            return;
        }
        esp_netif_ip_info_t info_t;
        memset(&info_t, 0, sizeof(esp_netif_ip_info_t));
        ipaddr_aton((const char *)S_IP, &info_t.ip.addr);
        ipaddr_aton((const char *)GATEWAY, &info_t.gw.addr);
        ipaddr_aton((const char *)NETMASK, &info_t.netmask.addr);
        if(esp_netif_set_ip_info(eth_netif, &info_t) != ESP_OK){
            ESP_LOGE(TAG, "Failed to set ip info");
        }
    #endif /* STATIC_IP */

    // Attach Ethernet driver to TCP/IP stack
    ESP_ERROR_CHECK(esp_netif_attach(eth_netif, esp_eth_new_netif_glue(eth_handles[0])));
    
    // Register user defined event handers
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, &eth_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &got_ip_event_handler, NULL));

    // Start Ethernet driver state machine
    for (int i = 0; i < eth_port_cnt; i++) {
        ESP_ERROR_CHECK(esp_eth_start(eth_handles[i]));
    }

    EventBits_t bits = xEventGroupWaitBits(s_eth_event_group,
                                           ETHERNET_CONNECTED_BIT | ETHERNET_FAIL_BIT,
                                           pdFALSE,
                                           pdFALSE,
                                           portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, 
     ** hence we can test which event actually happened. 
     */
    if (bits & ETHERNET_CONNECTED_BIT) {
        ESP_LOGI(ETH_TAG, "Ethernet Connection established.\n");
    } else if (bits & ETHERNET_FAIL_BIT) {
        ESP_LOGE(ETH_TAG, "Ethernet Connection Failed.");
    } else {
        ESP_LOGE(ETH_TAG, "UNEXPECTED EVENT");
    }
}

#endif /* ETHERNET_CONFIG */

/* MQTT Configuration */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(MQTT_TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);

    esp_mqtt_event_handle_t event = event_data;
    client = event->client;

    int msg_id;

    switch ((esp_mqtt_event_id_t)event_id) 
    {
        /* The client has successfully established a connection to the broker. 
           The client is now ready to send and receive data. */
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_CONNECTED");

            /* int esp_mqtt_client_subscribe(esp_mqtt_client_handle_t client, const char *topic, int qos) */
            msg_id = esp_mqtt_client_subscribe(client, "receive_from_ros", 0); /*receive control actions */
            msg_id = esp_mqtt_client_subscribe(client, "change_rate", 0);      /*receive rate at which data sent from the carr*/
            ESP_LOGI(MQTT_TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;

        /* The client has aborted the connection due to being unable to read or write data,
           e.g., because the server is unavailable. */
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DISCONNECTED");
            esp_mqtt_client_reconnect(client);
            break;

        /* The broker has acknowledged the client's subscribe request.
           The event data contains the message ID of the subscribe message. */
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        /* The broker has acknowledged the client's unsubscribe request.
           The event data contains the message ID of the unsubscribe message. */
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;

        /* The broker has acknowledged the client's publish message. 
           This is only posted for QoS level 1 and 2, as level 0 does not use acknowledgements.
           The event data contains the message ID of the publish message. */
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;

        /* The client has received a publish message. 
           The event data contains: message ID, name of the topic
           it was published to, received data and its length.  */
        case MQTT_EVENT_DATA:
            #if VERBOSE_LOG
                ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DATA : Recieved a publish message !");
                ESP_LOGI(MQTT_TAG, "TOPIC=%.*s\r\n", event->topic_len, event->topic);
                ESP_LOGI(MQTT_TAG, "DATA=%.*s\r\n", event->data_len, event->data);
            #endif


            /* Latency */
            /* int esp_mqtt_client_publish(esp_mqtt_client_handle_t client, const char *topic, const char *data, int len, int qos, int retain) */
            // msg_id = esp_mqtt_client_publish(client, "send_to_ros", event->data, event->data_len, 0, 0);

            mqtt_message tx_frame;


            #if VERBOSE_LOG
                ESP_LOGI(MQTT_TAG,"Throttle data : %f\n",tx_frame.throttle.f32);
                ESP_LOGI(MQTT_TAG,"Steering data : %f\n",tx_frame.steering.f32);
            #endif


            if(!strncmp(event->topic,"receive_from_ros",event->topic_len)){
                parse_double(event->data,&(tx_frame));
                tx_frame.canid = ID_CTRL;
            }else if(!strncmp(event->topic,"change_rate",event->topic_len)){
                tx_frame.throttle.f32 = (float)strtod(event->data, NULL);
                tx_frame.canid = ID_RATE;
                
            }else{
                ESP_LOGE(MQTT_TAG,"Error, incorrect topic\tTopic name : %s", event->topic);
            }
            
            if(xQueueSend(frame_queue_tx,(void *) &tx_frame,0) != pdPASS){
                ESP_LOGE(MQTT_TAG,"Error, Queue should never be full!");
            }
            break;

        case MQTT_EVENT_ERROR:
            ESP_LOGI(MQTT_TAG, "MQTT_EVENT_ERROR");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
                log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
                log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
                ESP_LOGI(MQTT_TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
            }
            break;
        default:
            ESP_LOGI(MQTT_TAG, "Other event id:%d", event->event_id);
            break;
    }
}

static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MQTT_HOST,
    };
    /* or : esp_err_t esp_mqtt_client_set_uri(esp_mqtt_client_handle_t client, const char *uri) */

    client = esp_mqtt_client_init(&mqtt_cfg);
    
    if(client == NULL){
        ESP_LOGE(MQTT_TAG, "MQTT Client creation failed.\n");
    }else{
        ESP_LOGI(MQTT_TAG, "MQTT Client successfuly created.\n");
    }

    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    /* esp_err_t esp_mqtt_client_register_event(esp_mqtt_client_handle_t client, esp_mqtt_event_id_t event, 
       esp_event_handler_t event_handler, void *event_handler_arg) */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);

    /* Starts MQTT client with already created client handle. */
    esp_mqtt_client_start(client);
}

/* CAN Tasks */
void twai_receive_task(void *param)
{
    // xSemaphoreTake(rx_sem, portMAX_DELAY);
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    
    twai_message_t rx_message;
    mqtt_message data;

    for(;;)
    {
        /* Block until a message is recieved */
        esp_err_t status = twai_receive(&rx_message, portMAX_DELAY);
        if (status == ESP_OK) {
            data.throttle.bytes.u8_1 = rx_message.data[0];
            data.throttle.bytes.u8_2 = rx_message.data[1];
            data.throttle.bytes.u8_3 = rx_message.data[2];
            data.throttle.bytes.u8_4 = rx_message.data[3];

            data.steering.bytes.u8_1 = rx_message.data[4];
            data.steering.bytes.u8_2 = rx_message.data[5];
            data.steering.bytes.u8_3 = rx_message.data[6];
            data.steering.bytes.u8_4 = rx_message.data[7];

            #if VERBOSE_LOG 
                ESP_LOGW(TWAI_TAG,"twai_receive_task : Msg received");
                ESP_LOGW(TWAI_TAG,"Throttle: %f\t Steering : %f \n",data.throttle.f32,data.steering.f32);
            #endif

            // snprintf returns number of characters that would have been stored 
            // in the array (not including the null character) had there been no length restriction
            
            int len = snprintf(NULL, 0, "%f", data.steering.f32);
            len += 1 ;                                                                 // add space between steering and throttle
            len += snprintf(NULL, 0, "%f", data.throttle.f32);                         // length of string of two values (no null termination)

            // ESP_LOGI(MQTT_TAG,"Length = %d",len);

            assert(len<BUFFER_SIZE);                                                   // check length doesnt exceed MAX size

            // char *result = malloc(len + 1);
            char result[BUFFER_SIZE];                                                  // avoid many dynamic allocations as it may cause fragmentation
            snprintf(result, len + 1, "%f %f", data.throttle.f32,data.steering.f32);   // always null terminates.
            
            #if VERBOSE_LOG
                ESP_LOGW(TWAI_TAG,"Publishing data : %s\n",result);
            #endif
            esp_mqtt_client_publish(client,"send_to_ros",result,len,0,0);

            // free(result); 

            /* Publish recieved message to mqtt */
            // if(rx_message.identifier == ID_CTRL){
            //     esp_mqtt_client_publish(client, "readings/steering",(const char *) rx_message.data, rx_message.data_length_code, 0, 0);
            // }else{
            //     esp_mqtt_client_publish(client, "readings/throttle", (const char *) rx_message.data, rx_message.data_length_code, 0, 0);
            // }
        } else if(status == ESP_ERR_TIMEOUT){
            ESP_LOGE(TWAI_TAG,"Timed out waiting for message\n");
        } else if(status == ESP_ERR_INVALID_ARG){
            ESP_LOGE(TWAI_TAG,"Arguments are invalid\n");
        } else if(status == ESP_ERR_INVALID_STATE){
            ESP_LOGE(TWAI_TAG,"TWAI driver is not installed\n");
        }else{
            ESP_LOGE(TWAI_TAG,"Unknown Error\n");
        }
    }
}

void twai_transmit_task(void * param)
{
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    twai_status_info_t status;
    twai_get_status_info(&status);
    if(status.state == TWAI_STATE_RUNNING){
        ESP_LOGI(TWAI_TAG, "TWAI is in running state.\n");
    }else{
        ESP_LOGE(TWAI_TAG, "TWAI not in functional state.\n");
    }

    twai_message_t tx_msg = {
        .data_length_code = 8, 
        .identifier = ID_CTRL,
        .extd = 0,                          // Standard Format message (11-bit ID)
        .rtr = 0,                           // Send a data frame
        .ss = 0,                            // Not single shot
        .self = 0,                          // Not a self reception request
        .dlc_non_comp = 0,                  // DLC is less than 8 (compliant)
    };


    for (;;)
    {
        mqtt_message tx_frame;
        /* Block until an mqtt message is recieved */
        if(xQueueReceive(frame_queue_tx,&tx_frame,portMAX_DELAY) == pdPASS)
        {
            tx_msg.data[0] = tx_frame.throttle.bytes.u8_1 ;
            tx_msg.data[1] = tx_frame.throttle.bytes.u8_2 ;
            tx_msg.data[2] = tx_frame.throttle.bytes.u8_3 ;
            tx_msg.data[3] = tx_frame.throttle.bytes.u8_4 ;

            tx_msg.data[4] = tx_frame.steering.bytes.u8_1 ;
            tx_msg.data[5] = tx_frame.steering.bytes.u8_2 ;
            tx_msg.data[6] = tx_frame.steering.bytes.u8_3 ;
            tx_msg.data[7] = tx_frame.steering.bytes.u8_4 ;
            // if(tx_frame.canid == 0xEF){
            //     tx_msg.data_length_code = 2;
            //     tx_msg.data[0] = tx_frame.throttle.bytes.u8_3 ;
            //     tx_msg.data[1] = tx_frame.throttle.bytes.u8_4 ;
            //     printf("hello\n");
            // }else{
            //     tx_msg.data[0] = tx_frame.throttle.bytes.u8_1 ;
            //     tx_msg.data[1] = tx_frame.throttle.bytes.u8_2 ;
            //     tx_msg.data[2] = tx_frame.throttle.bytes.u8_3 ;
            //     tx_msg.data[3] = tx_frame.throttle.bytes.u8_4 ;
    
            //     tx_msg.data[4] = tx_frame.steering.bytes.u8_1 ;
            //     tx_msg.data[5] = tx_frame.steering.bytes.u8_2 ;
            //     tx_msg.data[6] = tx_frame.steering.bytes.u8_3 ;
            //     tx_msg.data[7] = tx_frame.steering.bytes.u8_4 ;
            // }
            tx_msg.identifier = tx_frame.canid;
            
            /* Transmit on CAN BUS */
            esp_err_t twai_status = twai_transmit(&tx_msg, pdMS_TO_TICKS(100));

            switch (twai_status)
            {
                case ESP_OK:
                    #if VERBOSE_LOG
                        ESP_LOGI(TWAI_TAG,"Message queued for transmission\n");
                    #endif
                    break;
                case ESP_ERR_INVALID_ARG:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, Arguments are invalid \n");
                    break;
                case ESP_ERR_TIMEOUT:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, Timed out waiting for space on TX queue \n");
                    break;
                case ESP_FAIL:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, TX queue is disabled and another message is currently transmitting \n");
                    break;
                case ESP_ERR_INVALID_STATE:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, TWAI driver is not in running state, or is not installed \n");
                    break;
                case ESP_ERR_NOT_SUPPORTED:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, Listen Only Mode does not support transmissions \n");
                    break;
                default:
                    ESP_LOGE(TWAI_TAG,"Failed to queue message for transmission, Unknown Error ! \n");
                    break;
            }
        }else {
            ESP_LOGE(TWAI_TAG,"Error : Queue should never wakeup from block.");
        }
    }
}

void twai_alerts_task(void *param)
{
    // xSemaphoreTake(read_alerts_sem, portMAX_DELAY);
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    while (1) 
    {
        uint32_t alerts;
        /* this function will block until an alert occurs or until it timeouts. */
        twai_read_alerts(&alerts, portMAX_DELAY);
        
        if (alerts & TWAI_ALERT_ABOVE_ERR_WARN) {
            ESP_LOGE(TWAI_TAG, "Surpassed Error Warning Limit");
        }
        if (alerts & TWAI_ALERT_ERR_PASS) {
            ESP_LOGE(TWAI_TAG, "Entered Error Passive state");
        }
        if (alerts & TWAI_ALERT_BUS_OFF) {
            ESP_LOGE(TWAI_TAG, "Bus Off state");
            //Prepare to initiate bus recovery, reconfigure alerts to detect bus recovery completion
            twai_reconfigure_alerts(TWAI_ALERT_BUS_RECOVERED, NULL);
            for (int i = 3; i > 0; i--) {
                ESP_LOGW(TWAI_TAG, "Initiate bus recovery in %d", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
            twai_initiate_recovery();    // Needs 128 occurrences of bus free signal
            ESP_LOGE(TWAI_TAG, "Initiate bus recovery");
        }
        if (alerts & TWAI_ALERT_BUS_RECOVERED) {
            ESP_LOGI(TWAI_TAG, "Bus Recovered");
            ESP_ERROR_CHECK(twai_start());
            ESP_LOGI(TWAI_TAG, "Driver started");
        }
    }
}

void app_main(void)
{
    #if ETHERNET_CONFIG
        ethernet_setup();
    #endif
    #if WIFI_CONFIG
        wifi_init_sta();
    #endif

    vTaskDelay(2000/portTICK_PERIOD_MS);

    

    frame_queue_tx = xQueueCreate(10,sizeof(mqtt_message));

    TaskHandle_t twai_transmit_handle;
    xTaskCreatePinnedToCore(twai_transmit_task, "TWAI_tx", 4096, NULL, TX_TASK_PRIO, &twai_transmit_handle, tskNO_AFFINITY);

    TaskHandle_t twai_receive_handle;
    xTaskCreatePinnedToCore(twai_receive_task, "TWAI_rx", 4096, NULL, RX_TASK_PRIO, &twai_receive_handle, tskNO_AFFINITY);


    TaskHandle_t twai_alerts_handle;
    xTaskCreatePinnedToCore(twai_alerts_task, "TWAI_alerts", 4096, NULL, ALERT_TSK_PRIO, &twai_alerts_handle, tskNO_AFFINITY);

    // Install TWAI driver
    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_LOGI(TWAI_TAG, "Driver installed");

    ESP_ERROR_CHECK(twai_start());
    ESP_LOGI(TWAI_TAG, "Driver started");

    twai_reconfigure_alerts(TWAI_ALERT_ABOVE_ERR_WARN | TWAI_ALERT_ERR_PASS | TWAI_ALERT_BUS_OFF, NULL);

    mqtt_app_start();
    
    

    // Task notifications lighter than semaphores
    xTaskNotifyGive(twai_receive_handle);
    xTaskNotifyGive(twai_alerts_handle);
    xTaskNotifyGive(twai_transmit_handle);

}