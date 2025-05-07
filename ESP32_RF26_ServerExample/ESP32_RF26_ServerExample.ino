// rf24_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF24 class. RH_RF24 class does not provide for addressing or
// reliability, so you should only use RH_RF24  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf24_client
// Tested on Anarduino Mini http://www.anarduino.com/mini/ with RFM24W and RFM26W


//RH_RF24 rf24(14, 32, 27, hardware_spi); // ESP32
#include "manager.h"


void setup() 
{
  Serial.begin(9600);
  while (!Serial) {}
  initRF26();


  // Defaults after init are 434.0MHz, modulation GFSK_Rb5Fd10, power 0x10
//  if (!rf24.setFrequency(433.0))
//    Serial.println("setFrequency failed");

}

void loop()
{
  recLoop();
}