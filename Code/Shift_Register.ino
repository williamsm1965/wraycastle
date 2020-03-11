int DSpin = 8;
int STCPpin = 9;
int SHCPpin = 10;
int SRCpin = 11;
const int registers=8;
byte b= B10101010;
boolean Registers[registers];
void setup()
{
pinMode (DSpin, OUTPUT);
pinMode (STCPpin, OUTPUT);
pinMode (SHCPpin, OUTPUT);
pinMode (SRCpin, OUTPUT);
writeReg();
digitalWrite (SRCpin, LOW);  
}

void writeReg()
{
  digitalWrite (STCPpin, LOW);
  for (int i = registers-1; i>=0; i--)
  {
  digitalWrite (SHCPpin, LOW);
  digitalWrite (DSpin, Registers[i]);
  digitalWrite (SHCPpin, HIGH);
  }
  digitalWrite (STCPpin, HIGH);
}
void loop() {
  digitalWrite (SRCpin, HIGH);
for (int i = 0; i<= registers-1; i++)  
{
  Registers[i]= bitRead(b,i);
  delay(100);
  writeReg();
}
delay(1000);
  while(true){}
for (int i = registers-1; i>=0; i--)
{
  Registers[i]= LOW;
  delay(100);
  writeReg();
}
  delay(1000);
}
