#pragma once

class IAmbientSensor {

public:

    virtual ~IAmbientSensor() = default;

    virtual bool begin() = 0;

    virtual float temperature() = 0;

    virtual float pressure() = 0;

};