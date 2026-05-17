#pragma once
#include "Matrix.h"

class ILoss {
    public:
        virtual ~ILoss() = default;
        virtual double calcLoss(const Matrix& predicted, const Matrix& target) const = 0;
        virtual Matrix calcGrad(const Matrix& predicted, const Matrix& target) const = 0;
};