#include <SPI.h>
#include "RF24.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(2,15);
/**********************************************************/

byte slave[6] = "XXXXX";


void setup() {
  Serial.begin(115200);
  radio.begin();

  radio.setPALevel(RF24_PA_LOW);
  memset (slave,0,6);
  slave[0]='N';
  slave[1]=63;
  radio.setChannel (63);
  radio.openReadingPipe(1,slave);
  radio.printDetails ();
  // Start the radio listening for data
  radio.startListening();
  
}

void loop() {    
  if (radio.available ()){
    while (radio.available() ){                             
       long batteryLevel;
       radio.read( &batteryLevel, sizeof(long) );     
       Serial.println (batteryLevel);
    }
  }       
}


