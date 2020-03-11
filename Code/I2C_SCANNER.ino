#include <Wire.h>

const int numsensors = 127;
uint8_t SensorAdr[numsensors];
uint8_t adr1, adr2, adr3, adr4;

void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
  int j;
  Serial.println("Scanning...");
 

    for(address = 1; address < 127; address++ )
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      Wire.write(0x3c);
      Wire.write(0x02);
      Wire.write(0x00);
      error = Wire.endTransmission();
      if (error != 2)
      {
          Serial.print(address, HEX);
          Serial.print(": ");
          Serial.print(error);
          Serial.print(" , ");
        }
      if (error == 0)
      {
       Serial.print("I2C device found at address 0x");
        if (address<16)
          Serial.print("0");
          Serial.print(address,HEX);
          SensorAdr[numsensors] = (address,DEC);
          Serial.println("  !");
       j++;
       }
      else if (error==4)
      {
        Serial.print("Unknown error at address 0x");
        if (address<16)
          Serial.print("0");
         Serial.println(address,HEX);
      }   

    }


 

  delay(5000);           // wait 5 seconds for next scan

  Serial.println("Sensor Adresses:");
//  Serial.println(SensorAdr[numsensors]);
//  Serial.println(numsensors);
//  Serial.println(SensorAdr[30]);
//  Serial.println(adr1);
//  Serial.println(adr2);
//  Serial.println(adr3);
//  Serial.println(adr4);
 
}
