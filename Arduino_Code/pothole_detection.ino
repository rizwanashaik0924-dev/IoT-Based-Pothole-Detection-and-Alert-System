#include <SoftwareSerial.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

SoftwareSerial gpsSerial(4,3);
SoftwareSerial esp8266(7,8);

float thresholdDepth = 15.0;

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  gpsSerial.begin(9600);
  esp8266.begin(9600);

  Serial.println("Pothole Detection Started");
}

float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

void loop()
{
  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance > thresholdDepth)
  {
    Serial.println("POTHOLE DETECTED");
  }

  delay(1000);
}