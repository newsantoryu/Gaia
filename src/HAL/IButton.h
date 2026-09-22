#pragma once

class IButton {
public:
    virtual ~IButton() = default;

    virtual void begin() = 0;
    virtual void update() = 0;
    virtual bool wasPressed() = 0;
};