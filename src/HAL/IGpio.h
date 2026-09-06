#pragma once

class IGpio {
public:
    virtual ~IGpio() = default;

    virtual void begin() = 0;
    virtual void setHigh() = 0;
    virtual void setLow() = 0;
    virtual bool read() const = 0;
};