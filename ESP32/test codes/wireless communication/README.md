# test the whole cycle of communication via wireless channel
1. connect the ESP32 to a network via WIFI
2. connect the laptop to the same network
3. send control actions from the laptop to the ESP32 through a broker
    - the laptop must publish the datat to a speific topic in the broker
    - the ESP32 must subscribe for the same topic
4. forward the received control actions to the CAN bus with ID based on type of control action
    - speed with id =   0x04
    - orientation with id = 0x12
  