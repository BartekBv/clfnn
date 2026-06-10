#pragma once
#include "IActivation.h"
#include "Matrix.h"

class Softmax : public IActivation {
    public:
        Softmax() = default;
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};