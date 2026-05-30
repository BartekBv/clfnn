#pragma once
#include "IActivation.h"


class Sigmoid : public IActivation {
    private:
        double steepness;

    public:
        explicit Sigmoid(double steepness = 1.0);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};