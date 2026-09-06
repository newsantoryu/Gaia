#pragma once

class ISoilMoistureSensor {

public:

    virtual ~ISoilMoistureSensor() = default;

    virtual bool begin() = 0;

    virtual int readRaw() = 0;
};