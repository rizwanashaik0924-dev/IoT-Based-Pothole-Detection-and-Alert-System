#include <SoftwareSerial.h>

SoftwareSerial gps(4, 3);

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
}

void loop() {
  while (gps.available()) {
    Serial.write(gps.read());
  }
}