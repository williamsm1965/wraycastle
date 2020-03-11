#include <Servo.h>
const int trigPin = 10; // or could be A0
const int echoPin = 11; // or could be A1
long duration;
int distance;
Servo myServo;
void setup() {
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
    myServo.attach(12);
}
void loop() {
 Serial.println();delay(1000);
 printDistance(+1,15,165);
 Serial.println(); delay(1000);
 printDistance(-1,165,15);
}
int printDistance(int inc,int i,int j){
  for(i;i!=j;i=i+inc){ 
        myServo.write(i);
        delay(10);
        distance = calculateDistance();
        if (i % 5==0){Serial.println();}
        Serial.print(i);
        Serial.print(" degs : ");
        Serial.print(distance);
        Serial.print("cm , ");
    }}
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
