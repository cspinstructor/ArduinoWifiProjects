#include <SoftwareSerial.h>

SoftwareSerial esp8266(2, 3);

void setup() {
  Serial.begin(9600);
  delay(1000);
  esp8266.begin(9600);
  delay(1000);

  Serial.println("Started");
}

void loop() {
  if (esp8266.available()) {
    Serial.println(esp8266.readStringUntil("\n"));
  }
  if (Serial.available()) {
    esp8266.write(Serial.read());
  }
}
