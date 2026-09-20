#pragma once
#include "ILoss.h"

/**
 * @brief Implementation of the Categorical Cross-Entropy loss function.
 * Used to evaluate prediction error in multi-class classification problems.
 * Designed to work directly with the Softmax activation function.
 * Computes the loss value based on the predicted probabilities and the actual labels, as well as the gradient needed for backpropagation.
 * Stores the last computed loss value, which can be returned by the getLastCalculatedLoss() method.
 * The getName() method returns the abbreviation "CCE".
 */

class CatCrossEntropy : public ILoss {
    private:
        mutable double lastCalculatedLoss = 0.0;

    public:
        std::string getName() const override { return "CCE"; }
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
        double getLastCalculatedLoss() const override;
};