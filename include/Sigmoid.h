#pragma once
#include "IActivation.h"


class Sigmoid : public IActivation {
    public:
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};