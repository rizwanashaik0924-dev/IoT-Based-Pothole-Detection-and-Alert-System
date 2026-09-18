#include <SoftwareSerial.h>

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10

// GPS Module Pins
SoftwareSerial gpsSerial(4, 3);

// ESP8266 Communication Pins
SoftwareSerial esp8266(7, 8);

float thresholdDepth = 15.0; // cm

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  gpsSerial.begin(9600);
  esp8266.begin(9600);

  Serial.println("IoT Pothole Detection System Started");
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

void sendAlert(float depth) {

  // Example GPS coordinates
  String latitude = "16.5062";
  String longitude = "80.6480";

  Serial.println("=== POTHOLE DETECTED ===");
  Serial.print("Depth: ");
  Serial.print(depth);
  Serial.println(" cm");

  Serial.print("Latitude: ");
  Serial.println(latitude);

  Serial.print("Longitude: ");
  Serial.println(longitude);

  String message =
      "Pothole Alert | Depth: " +
      String(depth) +
      " cm | Lat: " +
      latitude +
      " | Lon: " +
      longitude;

  esp8266.println(message);

  Serial.println("Alert Sent Successfully");
}

void loop() {

  float distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > thresholdDepth) {
    sendAlert(distance);
  }

  delay(1000);
}