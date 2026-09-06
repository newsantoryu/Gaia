#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "Config/HardwareConfig.h"
#include "HAL/IAmbientSensor.h"

class Bmp180Sensor : public IAmbientSensor {

public:

    bool begin() override {

        Wire.setPins(
            HardwareConfig::I2C_SDA_PIN,
            HardwareConfig::I2C_SCL_PIN
        );

        if (!Wire.begin()) {
            return false;
        }

        if (!isConnected()) {
            return false;
        }

        return readCalibration();
    }

    float temperature() override {

        int32_t uncompensatedTemperature = 0;

        if (!readUncompensatedTemperature(
                uncompensatedTemperature
            )) {
            return NAN;
        }

        return calculateTemperature(
            uncompensatedTemperature
        );
    }

    float pressure() override {
        return NAN;
    }

private:

    static constexpr uint8_t I2C_ADDRESS = 0x77;

    static constexpr uint8_t REG_CALIBRATION_START = 0xAA;

    static constexpr uint8_t REG_CONTROL = 0xF4;

    static constexpr uint8_t REG_DATA = 0xF6;

    static constexpr uint8_t COMMAND_TEMPERATURE = 0x2E;

    struct Calibration {

        int16_t AC1;
        int16_t AC2;
        int16_t AC3;

        uint16_t AC4;
        uint16_t AC5;
        uint16_t AC6;

        int16_t B1;
        int16_t B2;

        int16_t MB;
        int16_t MC;
        int16_t MD;
    };

    Calibration calibration_{};

    bool isConnected() {

        Wire.beginTransmission(I2C_ADDRESS);

        return Wire.endTransmission() == 0;
    }

    bool readCalibration() {

        Wire.beginTransmission(I2C_ADDRESS);

        Wire.write(REG_CALIBRATION_START);

        if (Wire.endTransmission(false) != 0) {
            return false;
        }

        constexpr uint8_t CALIBRATION_SIZE = 22;

        if (
            Wire.requestFrom(
                I2C_ADDRESS,
                CALIBRATION_SIZE
            ) != CALIBRATION_SIZE
        ) {
            return false;
        }

        calibration_.AC1 = readSigned16();
        calibration_.AC2 = readSigned16();
        calibration_.AC3 = readSigned16();

        calibration_.AC4 = readUnsigned16();
        calibration_.AC5 = readUnsigned16();
        calibration_.AC6 = readUnsigned16();

        calibration_.B1 = readSigned16();
        calibration_.B2 = readSigned16();

        calibration_.MB = readSigned16();
        calibration_.MC = readSigned16();
        calibration_.MD = readSigned16();

        return calibrationIsValid();
    }

    int16_t readSigned16() {

        uint16_t value = readUnsigned16();

        return static_cast<int16_t>(value);
    }

    uint16_t readUnsigned16() {

        uint16_t msb = Wire.read();
        uint16_t lsb = Wire.read();

        return static_cast<uint16_t>(
            (msb << 8) | lsb
        );
    }

    bool calibrationIsValid() {

        return
            calibration_.AC1 != 0 &&
            calibration_.AC1 != -1 &&
            calibration_.AC2 != 0 &&
            calibration_.AC2 != -1 &&
            calibration_.AC3 != 0 &&
            calibration_.AC3 != -1 &&
            calibration_.AC4 != 0 &&
            calibration_.AC4 != 0xFFFF &&
            calibration_.AC5 != 0 &&
            calibration_.AC5 != 0xFFFF &&
            calibration_.AC6 != 0 &&
            calibration_.AC6 != 0xFFFF;
    }

    bool readUncompensatedTemperature(
        int32_t& temperature
    ) {

        Wire.beginTransmission(I2C_ADDRESS);

        Wire.write(REG_CONTROL);
        Wire.write(COMMAND_TEMPERATURE);

        if (Wire.endTransmission() != 0) {
            return false;
        }

        // BMP180 precisa de aproximadamente 4.5 ms
        // para completar a conversão de temperatura.
        delay(5);

        Wire.beginTransmission(I2C_ADDRESS);

        Wire.write(REG_DATA);

        if (Wire.endTransmission(false) != 0) {
            return false;
        }

        constexpr uint8_t TEMPERATURE_DATA_SIZE = 2;

        if (
            Wire.requestFrom(
                I2C_ADDRESS,
                TEMPERATURE_DATA_SIZE
            ) != TEMPERATURE_DATA_SIZE
        ) {
            return false;
        }

        uint16_t msb = Wire.read();
        uint16_t lsb = Wire.read();

        temperature =
            static_cast<int32_t>(
                (msb << 8) | lsb
            );

        return true;
    }

    float calculateTemperature(
        int32_t uncompensatedTemperature
    ) {

        int32_t x1 =
            (
                (
                    uncompensatedTemperature -
                    static_cast<int32_t>(calibration_.AC6)
                ) *
                static_cast<int32_t>(calibration_.AC5)
            ) >> 15;

        int32_t divisor =
            x1 +
            static_cast<int32_t>(calibration_.MD);

        if (divisor == 0) {
            return NAN;
        }

        int32_t x2 =
            (
                static_cast<int32_t>(calibration_.MC)
                << 11
            ) / divisor;

        int32_t b5 = x1 + x2;

        int32_t temperature =
            (b5 + 8) >> 4;

        return static_cast<float>(temperature) / 10.0f;
    }
};