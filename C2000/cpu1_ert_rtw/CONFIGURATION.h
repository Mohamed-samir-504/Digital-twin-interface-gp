/*
 * CONFIGURATION.h
 *
 *  Created on: Jun 18, 2024
 *      Author: Mark
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define DEFAULT_TRASNMIT_RATE 100
#define CAN_RECIEVE_SETPOINT_MSG_ID 0xA0
#define CAN_RECIEVE_RATE_MSG_ID 0xEF
#define MSG_DATA_LENGTH_RX    0   // "Don't care" for a Receive mailbox
#define MSG_DATA_LENGTH_TX    8
#define RX_MSG_OBJ1_ID      1
#define RX_MSG_OBJ2_ID      3
   // Use mailbox 1
#define TX_MSG_OBJ_ID      2





#endif /* CONFIGURATION_H_ */
