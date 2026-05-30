#pragma once
#include "IActivation.h"

class ReLU : public IActivation {
    private:
        double alpha; //leaky ReLU parameter

    public:
        explicit ReLU(double alpha = 0.01);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};