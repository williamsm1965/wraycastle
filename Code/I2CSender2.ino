/*
 I2C_Master Echo Serial data to an I2C slave
*/
#include <Wire.h>
const int address = 5;  //the address to be used by the communicating devices
int leftpin = 13;
int rightpin = 11;
int centpin = 12;
int leftbuttonstate = 0;
int rightbuttonstate = 0;
int centbuttonstate = 0;
void setup()
{
   Wire.begin();
  pinMode(leftpin, INPUT);
  pinMode(rightpin, INPUT);
  pinMode(centpin, INPUT);
}
void loop()
{
String message = "";
int stringlength = message.length();
leftbuttonstate = digitalRead(leftpin);
rightbuttonstate = digitalRead(rightpin);
centbuttonstate = digitalRead(centpin);
  if (leftbuttonstate == HIGH ) {
     message = "Left@";
    stringlength = message.length();
  }
  if (rightbuttonstate == HIGH ) {
      message = "Right@";
    stringlength = message.length();
  }
  if (centbuttonstate == HIGH ) {
     message = "Centre@";
    stringlength = message.length();
  }   
   if (stringlength > 1){
    Wire.beginTransmission(address);
    Wire.write(message.c_str());
    Wire.endTransmission();
    delay(500);
    message = "";
    stringlength = message.length();
  }
}
