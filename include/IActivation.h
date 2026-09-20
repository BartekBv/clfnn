#pragma once
#include "Matrix.h"

/**
 * @brief Interface for activation functions.
 * Defines the methods required to compute the function's value during forward propagation
 * and its derivative for backward error propagation.
 */

class IActivation {
    public:
        virtual ~IActivation() = default;
        virtual Matrix compute(const Matrix& input) const = 0; // = 0 means the method must be implemented in the derived class
        virtual Matrix derivative(const Matrix& input) const = 0;
};