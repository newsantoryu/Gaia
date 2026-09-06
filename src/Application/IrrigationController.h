#pragma once

#include "Domain/IActuator.h"
#include "Domain/IrrigationState.h"

class IrrigationController {

public:

    explicit IrrigationController(
        IActuator& actuator
    )
        : actuator_(actuator),
          state_(IrrigationState::IDLE) {}

    void start() {

        if (state_ == IrrigationState::IRRIGATING) {
            return;
        }

        actuator_.turnOn();

        state_ = IrrigationState::IRRIGATING;
    }

    void stop() {

        if (state_ == IrrigationState::IDLE) {
            return;
        }

        actuator_.turnOff();

        state_ = IrrigationState::IDLE;
    }

    bool isRunning() const {
        return state_ == IrrigationState::IRRIGATING;
    }

    IrrigationState state() const {
        return state_;
    }

private:

    IActuator& actuator_;

    IrrigationState state_;
};