#include <Arduino.h>

#include "Config/HardwareConfig.h"
#include "Drivers/Esp32Button.h"

Esp32Button pumpButton(
    HardwareConfig::PUMP_BUTTON_PIN
);

Esp32Button fanButton(
    HardwareConfig::FAN_BUTTON_PIN
);

void setup() {
    Serial.begin(115200);

    pumpButton.begin();
    fanButton.begin();

    Serial.println("Gaia iniciada.");
}

void loop() {

    pumpButton.update();
    fanButton.update();

    if (pumpButton.wasPressed()) {
        Serial.println("Bomba de agua foi acionada");
    }

    if (fanButton.wasPressed()) {
        Serial.println("Acionou liga/desliga da FAN");
    }
}