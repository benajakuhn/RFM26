// rf24_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF24 class. RH_RF24 class does not provide for addressing or
// reliability, so you should only use RH_RF24 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf24_server.
// Tested on Anarduino Mini http://www.anarduino.com/mini/ with RFM24W and RFM26W

#include <SPI.h>
#include <RH_RF24.h>

// Singleton instance of the radio driver
RH_RF24 rf24(5,6,11, hardware_spi);
uint8_t syncWords[] = {0x40, 0x5E, 0x77, 0xFA};

void setup() 
{
  Serial.begin(9600);

  while(!Serial)

  if (!rf24.init()) {
    Serial.println("init failed");
    while(1); // give up
  }

  /*if(!rf24.setFrequency(868.0)){
    Serial.write("frequency swap failed");
  }*/

  rf24.setSyncWords(syncWords, sizeof(syncWords));

  Serial.println("init done");


  uint8_t partInfo_reply[8];
  Serial.println("Sending PART_INFO command...");
  if (rf24.command(RH_RF24_CMD_PART_INFO, NULL, 0, partInfo_reply, sizeof(partInfo_reply))) {
    Serial.println("PART_INFO command successful. Reply:");
    // Print the received bytes
    for (uint8_t i = 0; i < sizeof(partInfo_reply); i++) {
      Serial.print(partInfo_reply[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("PART_INFO command failed.");
  }
  // Defaults after init are 434.0MHz, modulation GFSK_Rb5Fd10, power 0x10
  //if (!rf24.setFrequency(868.0))
    //Serial.println("setFrequency failed");
}


void loop()
{
  while(1){} // just chill
  rf24.available();
  Serial.println("Sending to rf24_server");
  // Send a message to rf24_server
  uint8_t data[] = "Hello World!";
  rf24.send(data, sizeof(data));

  rf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf24.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (rf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf24_server running?");
  }
  delay(400);
}
 