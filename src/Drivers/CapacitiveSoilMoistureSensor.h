#pragma once

#include <Arduino.h>

#include "Config/HardwareConfig.h"
#include "HAL/ISoilMoistureSensor.h"

class CapacitiveSoilMoistureSensor final
    : public ISoilMoistureSensor {

public:

    bool begin() override {

        pinMode(
            HardwareConfig::SOIL_MOISTURE_PIN,
            INPUT
        );

        analogReadResolution(12);

        return true;
    }

    int readRaw() override {

    int minValue = 4095;
    int maxValue = 0;
    long total = 0;

    constexpr int samples = 32;

    for (int i = 0; i < samples; ++i) {

        const int value = analogRead(
            HardwareConfig::SOIL_MOISTURE_PIN
        );

        total += value;

        if (value < minValue) {
            minValue = value;
        }

        if (value > maxValue) {
            maxValue = value;
        }

        delay(2);
    }

    const int average =
        total / samples;

    Serial.print("SOIL ADC | MIN: ");
    Serial.print(minValue);

    Serial.print(" | MAX: ");
    Serial.print(maxValue);

    Serial.print(" | AVG: ");
    Serial.println(average);

    return average;
}
};