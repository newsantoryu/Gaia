#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("==============================");
    Serial.println("      SOPHIA GAIA TEST");
    Serial.println("==============================");
    Serial.println("ESP32-C6 ONLINE");
    Serial.println("USB CDC ONLINE");
    Serial.println("==============================");
}

void loop() {
    Serial.println("ALIVE");
    delay(1000);
}