#include <AFMotor.h>
#include <Wire.h>

AF_DCMotor motor1(1); //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
AF_DCMotor motor2(2); // left rear motor 2; right front motor 3;left front motor 4;
AF_DCMotor motor3(3); // right front motor 3;left front motor 4;
AF_DCMotor motor4(4); //left front motor 4;

int pingPin = A0;
int inPin = A1;
unsigned long duration, inches;
int indec, cmdec;
int inchonv = 147;
int cmconv = 58;
int cm = 20;
uint8_t packetID = 0;  
uint8_t xReading = 90; 
uint8_t yReading = 90;
int speed13 = 0;
int speed24 = 0;
int spinSpeed = 0;
const int timer = 50;

void setup() {
  pinMode(pingPin, OUTPUT);
  pinMode(inPin, INPUT);
  Wire.begin(5);                // join i2c bus with address #5
  Serial.begin(9600);           // start serial for output
  delay(1000);
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  // put your main code here, to run repeatedly: 
  cm = getDistance();
  if (yReading == 0 && xReading == 0 && packetID == 0) {halt();} //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
  if (yReading >= 85 && yReading <= 95){delay(50); halt();}
  if (xReading >= 85 && xReading <= 95){ if (speed13 > speed24){speed24 = speed13;} else {speed13 = speed24;}}
  if (yReading < 85 or yReading > 95) {speed13 = 50; speed24 = 50;}
  if (yReading < 65 or yReading > 115) {speed13 = 100; speed24 = 100;}
  if (yReading < 45 or yReading > 135) {speed13 = 150; speed24 = 150;}
  if (yReading < 25 or yReading > 155) {speed13 = 200; speed24 = 200;}
  if (packetID == 0){speed13 =0; speed24=0;}
  if (yReading < 85 && xReading >= 85 && xReading <= 95 && cm > 20){forward(speed13, speed24);}
  if (yReading > 95 && xReading >= 85 && xReading <= 95){reverse(speed13, speed24);}
  if (yReading >= 85 && yReading <= 95 && xReading < 30){spinLeft(100);}
  if (yReading >= 85 && yReading <= 95 && xReading > 150){spinRight(100);}
  if (yReading < 85 && xReading < 85 && packetID > 0 && cm > 20){forward(speed13 , 50);}//turn left
  if (yReading < 85 && xReading > 95 && packetID > 0 && cm > 20){forward(50 , speed24);}//turn right
  if (yReading > 95 && xReading < 85){reverse(speed13 , 50);}//turn left
  if (yReading > 95 && xReading > 95){reverse(50 , speed24);}//turn right

}

void forward (int spd1, int spd2) //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
{
  motor1.run(FORWARD);
  motor1.setSpeed(spd1);
  motor2.run(FORWARD);
  motor2.setSpeed(spd2);
  motor3.run(FORWARD);
  motor3.setSpeed(spd1);
  motor4.run(FORWARD);
  motor4.setSpeed(spd2);
  //delay (timer);
}

void reverse (int spd1, int spd2) //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
{
  motor1.run(BACKWARD);
  motor1.setSpeed(spd1);
  motor2.run(BACKWARD);
  motor2.setSpeed(spd2);
  motor3.run(BACKWARD);
  motor3.setSpeed(spd1);
  motor4.run(BACKWARD);
  motor4.setSpeed(spd2);
  //delay (timer);
}

void spinLeft (int spd) //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
{
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);
  motor2.run(BACKWARD);
  motor4.run(BACKWARD);
  motor1.run(FORWARD);
  motor3.run(FORWARD);
}

void spinRight (int spd) //right rear motor1; left rear motor 2; right front motor 3;left front motor 4;
{
  motor1.setSpeed(spd);
  motor2.setSpeed(spd);
  motor3.setSpeed(spd);
  motor4.setSpeed(spd);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
}

void halt()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

int getDistance()
{
  int rval;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  // duration = pulseIn(inPin, HIGH, 38000L);
  duration = pulseIn(inPin, HIGH, 20000);
   if (duration == 0)
    duration = 1190;
  rval = microsecondsToCentimeters(duration);
  return rval;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / cmconv;
}

void receiveEvent(int howMany)
{
  while(Wire.available()){  // slave may send less than requested
    
    // uint8_t xy = Wire.read(); // receive a byte as character 
      packetID = Wire.read(); // receive a byte as character 
      xReading = Wire.read(); //if (xy>0) {Serial.println(xy);}
      yReading = Wire.read();
      Serial.print(packetID);
      Serial.print(" , ");
       
}}
   
