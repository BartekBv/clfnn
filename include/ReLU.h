#pragma once
#include "IActivation.h"

/**
 * @brief Implementation of the Leaky ReLU activation function.
 * For positive values it returns the input value, and for negative values it returns the value multiplied by the alpha coefficient.
 * Also computes the derivative needed for backpropagation.
 */

class ReLU : public IActivation {
    private:
        double alpha; //leaky ReLU parameter

    public:
        explicit ReLU(double alpha = 0.01);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};