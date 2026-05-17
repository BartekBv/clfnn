#pragma once
#include "ILoss.h"

class MSE : public ILoss {
    public:
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
};