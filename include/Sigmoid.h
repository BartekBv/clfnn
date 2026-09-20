#pragma once
#include "IActivation.h"

/**
 * @brief Implementation of the Sigmoid activation function.
 * Maps input values to the (0, 1) range. The optional steepness parameter allows adjusting the curve's slope.
 * Also computes the derivative needed for backpropagation.
 */

class Sigmoid : public IActivation {
    private:
        double steepness;

    public:
        explicit Sigmoid(double steepness = 1.0);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};