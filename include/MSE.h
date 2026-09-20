#pragma once
#include "ILoss.h"

/**
 * @brief Implementation of the Mean Squared Error loss function.
 * Computes the mean of the squared differences between the prediction and the expected value.
 * Also computes the gradient needed for backpropagation. Stores the last computed loss value, which can be returned by getLastCalculatedLoss(). The getName() method returns the abbreviation "MSE".
 */

class MSE : public ILoss {
    private:
        mutable double lastCalculatedLoss = 0.0;
        
    public:
        std::string getName() const override { return "MSE"; }
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
        double getLastCalculatedLoss() const override;
};