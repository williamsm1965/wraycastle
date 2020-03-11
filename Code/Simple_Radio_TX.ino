/*
* Arduino Wireless Communication Tutorial
*     Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
1 - GND 
2 - VCC 3.3V !!! NOT 5V 
3 - CE to Arduino pin 9 
4 - CSN to Arduino pin 10 
5 - SCK to Arduino pin 13 
6 - MOSI to Arduino pin 11 
7 - MISO to Arduino pin 12 
8 - UNUSED
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pin allocation 

const byte address[6] = "00001"; // address for comms

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}
