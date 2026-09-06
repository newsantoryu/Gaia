#pragma once

#include <cstdint>

class IGpio {

public:

    virtual ~IGpio() = default;

    virtual void begin() = 0;

    virtual void setHigh() = 0;

    virtual void setLow() = 0;

    virtual bool read() const = 0;

    virtual void setPwm(
        uint8_t percentage
    ) = 0;
};