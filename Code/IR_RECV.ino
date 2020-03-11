#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)){
//        Serial.println(results.value, HEX);
//        Serial.println(results.value);
        irrecv.resume();

   switch (results.value) {
    case 16753245:    // remote control keys
      Serial.println("1");
      break;
    case 16736925:    // 
      Serial.println("2");
      break;
    case 16769565:    //
      Serial.println("3");
      break;
    case 16720605:    // 
      Serial.println("4");
      break;
    case 16712445:    // 
      Serial.println("5");
      break;
    case 16761405:    // 
      Serial.println("6");
      break;
    case 16769055:    // 
      Serial.println("7");
      break;
    case 16754775:    // 
      Serial.println("8");
      break;
    case 16748655:    // 
      Serial.println("9");
      break;   
    case 16750695:    // 
      Serial.println("0");
      break;                 
    case 16716015:    // 
      Serial.println("<--");
      break;
    case 16734885:    // 
      Serial.println("-->");
      break;
    case 16718055:    // 
      Serial.println("/\\");
      break;
    case 16730805:    // 
      Serial.println("\\/");
      break;  
    case 16738455:    // 
      Serial.println("*");
      break;
    case 16756815:    // 
      Serial.println("#");
      break;   
    case 16726215:    // 
      Serial.println("OK");
      break;         
  }
  
  }

}
