#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor(4);
AF_DCMotor motor2(3);

int steerPin = 10;
Servo steerServo;

int pingPin = A0;
int inPin = A1;
unsigned long duration, inches;
int indec, cmdec;
int inchonv = 147;
int cmconv = 58;
String s1, s2, s3;
int steerCentre = 60;

void setup() {
  // put your setup code here, to run once:
pinMode(pingPin, OUTPUT);
pinMode(inPin, INPUT);
steerServo.attach(steerPin, 1000, 2000);
steer(0);
}
void loop() {
  // put your main code here, to run repeatedly: 
  int cm, lcm, rcm;

  forward(200);
  delay(100);
  cm = getDistance();
  //Serial.println(cm);
  if(cm < 20)
{
    halt();
    reverse(100);
    delay(100);
    halt();
    steer(-60);
    lcm = getDistance();
    steer(60);
    rcm = getDistance();
    steer(0);
         
    if (lcm < rcm + 5)
        steer(-60);
      else
        steer(60); 
    reverse(180);
    delay(500);
    halt();
    if (lcm <= rcm + 10 and rcm <= lcm +10) 
        {
          steer(-60);
          forward(200);
          delay(100);
          halt();
        }      
    steer(0);
  }
}
void steer(int angle)
{
  steerServo.write(steerCentre + angle);
  delay(800);
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

void forward (int spd)
{
  motor.run(FORWARD);
  motor.setSpeed(spd);
  motor2.run(FORWARD);
  motor2.setSpeed(spd);
}

void reverse (int spd)
{
  motor.run(BACKWARD);
  motor.setSpeed(spd);
  motor2.run(BACKWARD);
  motor2.setSpeed(spd);
}

void spinLeft (int spd)
{
}

void spinRight (int spd)
{
}

void halt()
{
  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(10);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / cmconv;
}

