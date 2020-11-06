#include <NeoSWSerial.h>;
 
const int US100_TX = 2;
const int US100_RX = 3;
 
// Instancia nuevo canal serie
NeoSWSerial jsnSerial(US100_RX, US100_TX);
 
short int rxByte, msbDist, lsbDist, checksum, testsum;
unsigned int mmDist = 0;
#define TIMEOUT(x) (x == -1)

short int readSerial() {
    byte timeout = 100;
    while(!jsnSerial.available()) {
      delay(1);
      timeout--;
      if (timeout == 0) {
        Serial.println("Timeout");
        return -1;
      }
    }
    return jsnSerial.read();
}

void setup() {
    Serial.begin(115200);
    jsnSerial.begin(9600);
}

void loop() {
  for (;;) {
    jsnSerial.write(0x55);

    //delay(10);
    
    rxByte = readSerial();
    if (rxByte != 0xff)
      continue;
  
    msbDist = readSerial();
    if (TIMEOUT(msbDist))
      continue;
    
    lsbDist = readSerial();
    if (TIMEOUT(lsbDist))
      continue;
  
    checksum = readSerial();
    if (TIMEOUT(checksum))
      continue;
  
    testsum = (msbDist + lsbDist + 0xff) & 0xff;
    if (checksum != testsum) {
      Serial.println("Checksum FAILED");
      continue;
    }
  
    mmDist  = msbDist * 256 + lsbDist;      
    Serial.print("Distance ");
    Serial.print(mmDist, DEC);
    Serial.print(" mm");
    
    Serial.println();
  }
}
