#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 10, TX = digital pin 11

SoftwareSerial SoftwareSerial2(10, 11);

// software serial #2: RX = digital pin 8, TX = digital pin 9
// on the Mega, use other pins instead, since 8 and 9 don't work on the Mega

void setup() {
  Serial.begin(9600);
  SoftwareSerial2.begin(115200);
}

void loop() {
  // read from port 0, send to port 1:
  while (SoftwareSerial2.available() > 0) {

    char inByte = SoftwareSerial2.read();

    Serial.write(inByte);

  }
}
