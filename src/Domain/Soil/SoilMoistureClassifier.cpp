#include "SoilMoistureClassifier.h"

SoilState SoilMoistureClassifier::classify(int rawValue) const {

    if (rawValue <= 100) {
        return SoilState::CALIBRATE;
    }

    if (rawValue <= 180) {
        return SoilState::DRY;
    }

    if (rawValue <= 300) {
        return SoilState::MODERATE;
    }

    if (rawValue <= 500) {
        return SoilState::WET;
    }

    return SoilState::VERY_WET;
}