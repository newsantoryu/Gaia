#pragma once

#include "ISoilMoistureClassifier.h"

class SoilMoistureClassifier : public ISoilMoistureClassifier {
public:
    SoilState classify(int rawValue) const override;
};