/*
* Arduino Wireless Communication Tutorial
*       Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
String message;
RF24 radio(9, 10); // CE, CSN
int xyreading = 90;
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
     radio.read(&xyreading, sizeof(xyreading));
    Serial.println(xyreading);
 
  }
   
}
