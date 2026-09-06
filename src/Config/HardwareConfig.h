#pragma once

#include <cstdint>

namespace HardwareConfig {

    //atuadores
    constexpr uint8_t MOSFET_TRIG_PIN = 4;
    
   // I2C - BMP180
    constexpr uint8_t I2C_SDA_PIN = 6;
    constexpr uint8_t I2C_SCL_PIN = 7;

    // Sensor de umidade do solo
    constexpr uint8_t SOIL_MOISTURE_PIN = 0;
}