#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Wait for serial to initialize
  
  Serial.println("=================================");
  Serial.println("ESP32-S3 Serial Test");
  Serial.println("=================================");
  Serial.println("Board is working!");
  Serial.print("Free heap: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
}

void loop() {
  static unsigned long lastPrint = 0;
  static int counter = 0;
  
  // Print every 2 seconds
  if (millis() - lastPrint >= 2000) {
    lastPrint = millis();
    counter++;
    Serial.print("Loop counter: ");
    Serial.println(counter);
    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" seconds");
    Serial.println("---");
  }
}
