#pragma once
#include "Matrix.h"

/**
 * @brief Interface for loss functions.
 * Defines methods for computing the error value between a prediction and the actual value,
 * calculating the gradient needed for backpropagation, and returning the last computed loss value.
 */

class ILoss {
    public:
        virtual ~ILoss() = default;
        virtual std::string getName() const = 0;
        virtual double calcLoss(const Matrix& predicted, const Matrix& target) const = 0;
        virtual Matrix calcGrad(const Matrix& predicted, const Matrix& target) const = 0;
        virtual double getLastCalculatedLoss() const = 0;
};