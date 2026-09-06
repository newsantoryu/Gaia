#pragma once

#include "Domain/IActuator.h"

class IrrigationController {

public:

    explicit IrrigationController(
        IActuator& actuator
    )
        : actuator_(actuator) {}

    void start() {
        actuator_.turnOn();
    }

    void stop() {
        actuator_.turnOff();
    }

    bool isRunning() const {
        return actuator_.isOn();
    }

private:

    IActuator& actuator_;
};