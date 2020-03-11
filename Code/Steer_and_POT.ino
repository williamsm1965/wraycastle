/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

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
Servo servo_9;

void setup()
{
  servo_9.attach(9);
  pinMode(leftpin, INPUT);
  pinMode(rightpin, INPUT);
  pinMode(centpin, INPUT);

}

void loop()
{
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  pos = val;
  
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
  if (j=1) {
  for (i = oldpos; i <= pos; i += 1) {
    servo_9.write(pos);
  	delay(1);
  }}
    else {
    for (i = oldpos; i >= pos; i += -1) {
    servo_9.write(pos);
  	delay(1);
  }}
  
oldpos = pos;
}
