/*
 * I2C_Master
 * Echo Serial data to an I2C slave
 */
#include <Wire.h>
const int address = 5;  
//the address to be used by the communicating devices
void setup()
{
   Wire.begin();

}
void loop()
{
     struct record
{
   int throttle;
   int steer;
   int spinLeft;
   int spinRight;
   int halt;
};
typedef struct record Record;
char c;
Record packet;
packet.throttle = 100;
packet.steer=0;
packet.spinLeft=0;
packet.spinRight=0;
packet.halt=101;

String message = "Will trade for band merch. ";
int stringlength = message.length();
int i;   
        for (i = 0; i < stringlength; i++){
        c= message.charAt(i);
        delay(100);
        Wire.beginTransmission(address);
        Wire.write(c);
        Wire.endTransmission();}
      delay(500); 
        Wire.beginTransmission(address);
        Wire.write ((byte *)&packet, sizeof packet);
        Wire.endTransmission();  
}
