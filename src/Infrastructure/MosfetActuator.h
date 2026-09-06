#pragma once

#include "HAL/IGpio.h"
#include "Domain/IActuator.h"

class MosfetActuator final : public IActuator {

public:

    explicit MosfetActuator(
        IGpio& gpio,
        bool activeHigh = true
    )
        : gpio_(gpio),
          activeHigh_(activeHigh),
          state_(false) {}

    void turnOn() override {
        writeSignal(true);
        state_ = true;
    }

    void turnOff() override {
        writeSignal(false);
        state_ = false;
    }

    bool isOn() const override {
        return state_;
    }

    void setPower(uint8_t percentage) {

        if (percentage > 100) {
            percentage = 100;
        }

        const uint8_t signalPercentage =
            activeHigh_
                ? percentage
                : 100 - percentage;

        gpio_.setPwm(signalPercentage);

        state_ = percentage > 0;
    }

private:

    void writeSignal(bool actuatorOn) {

        const bool signal =
            activeHigh_
                ? actuatorOn
                : !actuatorOn;

        if (signal) {
            gpio_.setHigh();
        } else {
            gpio_.setLow();
        }
    }

    IGpio& gpio_;
    bool activeHigh_;
    bool state_;
};