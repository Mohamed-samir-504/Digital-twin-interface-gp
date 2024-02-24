/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <WiFi.h>
#include <PubSubClient.h>
// #include <WiFiClient.h>
#include <CAN.h>

#define powersaving 1
#define nagles 1


#define TX_GPIO_NUM   5  // Connects to CTX
#define RX_GPIO_NUM   4  // Connects to CRX

// Replace the next variables with your SSID/Password combination
const char* ssid = "wifi_name";
const char* password = "wifi_pass";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "192.168.1.5";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  delay(2000);
  // while (!Serial);
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  //status = bme.begin();  
 
  setup_wifi();
  setup_can();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}
void setup_can(){
  Serial.println ("Can Transmitter");

  // Set the pins
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
  
  // start the CAN bus at 500 kbps
  if (!CAN.begin (500E3)) {
    Serial.println ("Starting CAN failed!");
    while (1);
  }
  else {
    Serial.println ("CAN Initialized");
  }
}
void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");//.............
  }
  #ifdef powersaving
  WiFi.setSleep(false);
  #endif
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  if(String(topic) == "car/speed")
    can_send(0x04 , message, length);
  else if(String(topic) == "car/orientation")
    can_send(0x12 , message, length);
  
}

void can_send(unsigned int id, byte* message, unsigned int length){
  unsigned int current = 0;
  while(current < length){
    CAN.beginPacket (id);  //sets the ID and clears the transmit buffer
    for(unsigned int i = 0; i < 8 && current < length; i++){
      CAN.write(message[current++]);

    }
    CAN.endPacket();
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("car/speed");
      client.subscribe("car/orientation");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
