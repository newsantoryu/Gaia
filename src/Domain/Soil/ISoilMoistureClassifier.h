#pragma once

#include "SoilState.h"

class ISoilMoistureClassifier {
public:
    virtual ~ISoilMoistureClassifier() = default;

    virtual SoilState classify(int rawValue) const = 0;

};