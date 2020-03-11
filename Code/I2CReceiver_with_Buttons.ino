/*
Serial Receive to Serial Monitor
*/
#include <Servo.h>
#include <Wire.h>
#include <EEPROM.h>
int addr = 0;
String message = "";
int pos = 90;
int j = 1;
int i;
int oldpos = 90;
char c;
Servo myservo;
byte value;
void setup()
{
  myservo.attach(9);
  Wire.begin(5);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  
  EEPROM.write(799, 0xEF);
  Serial.println(EEPROM.length());
  for (j = 0; j < EEPROM.length(); j+=16){
  for (i=0; i < 16; i+= 1) {
  value = EEPROM.read(j+i);  
  Serial.print(value, HEX);
  Serial.print(" , ");
  }
  Serial.println(j+i-1);
}}

void loop()
{
if (j=1) {
  for (i = oldpos; i < pos; i += 1) {
    myservo.write(i);
    delay(1);
  }}
    else {
    for (i = oldpos; i > pos; i += -1) {
    myservo.write(i);
    delay(1);
  }}
 myservo.write(pos); 
oldpos = pos;}


void receiveEvent(int howMany)
{
while(Wire.available()){    // slave may send less than requested
    c = Wire.read(); // receive a byte as character 
        message += c; 
        if (message=="Right"){ 
          Serial.println("-->");
          pos = pos - 10;
          if (pos < 0) { pos = 0;}
          j=-1;
          message = "";
          }
        else if (message=="Left"){ 
          Serial.println("<--");
          pos = pos + 10;
          if (pos > 180) { pos = 180;}
          j=1;
          message = "";
          }
         else if (message=="Centre"){ 
          Serial.println("<->");
          j=1;
          if (pos > 90) { j=-1;}
          pos = 90;
          message = "";
          }
        //message += c; 
         //Serial.println( message); 
  }    
     //Serial.println(message); 
     //  Serial.print("Position :"+String(pos) + " " + "Old Position" +String(oldpos));
        message = ""; 
} 
