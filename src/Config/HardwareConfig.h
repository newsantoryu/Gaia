#pragma once

#include <cstdint>

namespace HardwareConfig {

    // Atuadores
    constexpr uint8_t PUMP_MOSFET_PIN = 0;
    constexpr uint8_t FAN_MOSFET_PIN = 4;

    // Botões
    constexpr uint8_t PUMP_BUTTON_PIN = 3;
    constexpr uint8_t FAN_BUTTON_PIN = 2;

    // I2C - BMP180
    constexpr uint8_t I2C_SDA_PIN = 6;
    constexpr uint8_t I2C_SCL_PIN = 7;

}