#pragma once

#include <Arduino.h>

#include "HAL/IButton.h"

class Esp32Button : public IButton {
public:
    explicit Esp32Button(uint8_t pin)
        : pin(pin) {
    }

    void begin() override {
        pinMode(pin, INPUT_PULLUP);

        stableState = HIGH;
        lastReading = HIGH;
        pressedEvent = false;
        lastDebounceTime = millis();
    }

    void update() override {
        const int reading = digitalRead(pin);

        // O sinal mudou: começa/reinicia a janela de debounce.
        if (reading != lastReading) {
            lastDebounceTime = millis();
            lastReading = reading;
        }

        // O sinal permaneceu estável durante o período de debounce.
        if ((millis() - lastDebounceTime) < debounceTime) {
            return;
        }

        // Só processa quando o estado estável realmente mudou.
        if (reading == stableState) {
            return;
        }

        const int previousState = stableState;
        stableState = reading;

        // Detecta exclusivamente a transição:
        // HIGH -> LOW
        if (previousState == HIGH && stableState == LOW) {
            pressedEvent = true;
        }
    }

    bool wasPressed() override {
        const bool event = pressedEvent;

        pressedEvent = false;

        return event;
    }

private:
    uint8_t pin;

    int stableState = HIGH;
    int lastReading = HIGH;

    bool pressedEvent = false;

    unsigned long lastDebounceTime = 0;

    static constexpr unsigned long debounceTime = 50;
};