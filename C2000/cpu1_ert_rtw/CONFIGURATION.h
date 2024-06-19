
#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define DEFAULT_TRASNMIT_RATE (uint32_t)100
#define CAN_RECIEVE_SETPOINT_MSG_ID 0xA0
#define CAN_RECIEVE_RATE_MSG_ID 0xEF
#define MSG_DATA_LENGTH_RX    0   // "Don't care" for a Receive mailbox
#define MSG_DATA_LENGTH_TX    8
#define RX_MSG_OBJ1_ID      1
#define RX_MSG_OBJ2_ID      3
#define TX_MSG_OBJ_ID      2

typedef union{
    uint32_t i;
    float f;
}transmit_rate_union;


#endif /* CONFIGURATION_H_ */
