#include "manager.h"

RH_RF24 rf24(5, 6, 11, hardware_spi);
uint8_t syncWords[] = {0x40, 0x5E, 0x77, 0xFA};

void initRF26(){
  if(!rf24.init()){
    Serial.println("init failed");
  }
  /*if(!rf24.setFrequency(868.0)){
    Serial.println("frequency swap failed");
  }*/
  rf24.setSyncWords(syncWords, sizeof(syncWords));

  Serial.println("init done");
}

void recLoop(){
    if (rf24.available()){
    // Should be a message for us now   
    uint8_t buf[RH_RF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf24.recv(buf, &len)){
//      RF24::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println((uint8_t)rf24.lastRssi(), DEC);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf24.send(data, sizeof(data));
      rf24.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}