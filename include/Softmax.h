#pragma once
#include "IActivation.h"
#include "Matrix.h"

/**
 * @brief Implementation of the Softmax activation function.
 * Normalizes input values into a probability distribution that sums to 1.
 * The derivative method is optimized to work directly with categorical cross-entropy.
 */

class Softmax : public IActivation {
    public:
        Softmax() = default;
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};