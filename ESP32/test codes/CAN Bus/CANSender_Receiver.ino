#include <CAN.h>

#define TX_GPIO_NUM   5  // Connects to CTX
#define RX_GPIO_NUM   4  // Connects to CRX

void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1000);

 // Serial.println ("CAN Receiver");
  Serial.println ("CAN Sender");

  // Set the pins
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);

  // start the CAN bus at 1 Mbps
  if (!CAN.begin(1000E3)) {
    Serial.println ("Starting CAN failed!");
    while (1); // halt if CAN initialization failed
  }
  else {
    Serial.println ("CAN Initialized");
  }
}

void loop() {
  // Uncomment one of the below lines to test sender or receiver
  canSender();
  //canReceiver();
}

void canSender() {
  Serial.print ("Sending packet ... ");

  CAN.beginPacket (0x12);
  CAN.write ('1');
  CAN.write ('2');
  CAN.write ('3');
  CAN.write ('4');
  CAN.write ('5');
  CAN.write ('6');
  CAN.write ('7');
  CAN.write ('8');
  if (CAN.endPacket() == 0) {
    Serial.println ("Transmission failed!");
  } else {
    Serial.println ("Transmission successful");
  }

  delay (1000);
}

void canReceiver() {
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    Serial.print ("Received ");

    if (CAN.packetExtended()) {
      Serial.print ("extended ");
    }

    if (CAN.packetRtr()) {
      Serial.print ("RTR ");
    }

    Serial.print ("packet with id 0x");
    Serial.print (CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print (" and requested length ");
      Serial.println (CAN.packetDlc());
    } else {
      Serial.print (" and length ");
      Serial.println (packetSize);

      while (CAN.available()) {
        Serial.print ((char) CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }
}
