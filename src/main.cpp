#include <Arduino.h>

#include "Drivers/CapacitiveSoilMoistureSensor.h"

CapacitiveSoilMoistureSensor soilSensor;

void setup() {

    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println("          SOPHIA GAIA");
    Serial.println("     SOIL MOISTURE TEST");
    Serial.println("================================");

    Serial.println("Inicializando sensor...");

    if (!soilSensor.begin()) {

        Serial.println("SOIL MOISTURE....... ERRO");

        return;
    }

    Serial.println("SOIL MOISTURE....... OK");
    Serial.println("ADC................. READY");

    Serial.println("================================");
    Serial.println("LENDO VALOR RAW");
    Serial.println("================================");
}

void loop() {

    int rawValue = soilSensor.readRaw();

    Serial.print("SOIL MOISTURE RAW... ");
    Serial.println(rawValue);

    delay(1000);
}
