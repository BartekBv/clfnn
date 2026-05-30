#pragma once
#include "ILoss.h"

class MSE : public ILoss {
    private:
        mutable double LastCalculatedLoss = 0.0;
    public:
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
        double getLastCalculatedLoss() const override;
};