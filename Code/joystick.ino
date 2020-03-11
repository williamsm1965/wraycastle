/*
 Controlling a servo position using a joystick
*/
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
Servo myservo2;
// Define Pins
const int joystickX = A1;         // joystick X axis  
const int joystickY = A2;       // joystick Y axis
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(7);
      pinMode(trigPin, OUTPUT); 
      pinMode(echoPin, INPUT);
      Serial.begin(9600);
}
void loop() {
  // read and scale the two axes:
  int xReading = readAxis(joystickX);
  int yReading = readAxis(joystickY);
  myservo.write(180-xReading);  
  myservo2.write(180-yReading);            
  delay(30); 
  distance = calculateDistance();
        Serial.print(distance);
        Serial.print(";");                                
}
// reads an axis (A1 or A2 for x or y) and scales the
int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);
  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, 180);
  return reading;
}
int calculateDistance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
    distance= duration*0.034/2;
    return distance;
}
