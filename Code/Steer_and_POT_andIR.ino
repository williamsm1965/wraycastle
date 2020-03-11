/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;


int pos = 90;
int leftpin = 13;
int rightpin = 11;
int centpin = 12;
int leftbuttonstate = 0;
int rightbuttonstate = 0;
int centbuttonstate = 0;
int potpin = 0;
int val;
int j = 1;
int i;
int oldpos = 90;
Servo myservo;

void setup()
{
  myservo.attach(9);
  pinMode(leftpin, INPUT);
  pinMode(rightpin, INPUT);
  pinMode(centpin, INPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);


}

void loop()
{
 // val = analogRead(potpin);
//  val = map(val, 0, 1023, 0, 180);
 // pos = val;
  
  leftbuttonstate = digitalRead(leftpin);
  rightbuttonstate = digitalRead(rightpin);
  centbuttonstate = digitalRead(centpin);

  if (leftbuttonstate == HIGH ) {
  pos = 180;
  j=1;
  }
  if (rightbuttonstate == HIGH ) {
  pos = 0;
  j=-1;
  }
  if (centbuttonstate == HIGH ) {
    if (pos > 90) { j = -1;} else {j = 1;}
  pos = 90;
  }
  
    if (irrecv.decode(&results)){
//        Serial.println(results.value, HEX);
        //Serial.println(results.value);
        irrecv.resume();

   switch (results.value) {
    case 16716015:    // 
      Serial.println("<--");
      pos = pos + 10;
      if (pos > 180) { pos = 180;}
            //Serial.println(pos);
      //Serial.println(oldpos);
      j=1;
      break;
    case 16734885:    // 
      Serial.println("-->");
      pos = pos - 10;
       if (pos < 0) { pos = 0;}
     // Serial.println(pos);
      //Serial.println(oldpos);
      j=-1;
      break;
      default:
      //if (pos > 90) {j=-1;} else if (pos < 90) {j = 1;}
      //pos = 90;
      break;
   }}
      //Serial.println(pos);
      //Serial.println(oldpos);
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
oldpos = pos;

}
