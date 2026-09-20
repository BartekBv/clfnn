#include "../include/CatCrossEntropy.h"
#include <cmath>
#include <algorithm>

double CatCrossEntropy::calcLoss(const Matrix& pred, const Matrix& target) const {
    double loss = 0.0;
    double epsilon = 1.0e-12; // small value to avoid log(0)

    for (int i = 0; i < pred.getRows(); i++) {
        for (int j = 0; j < pred.getCols(); j++) {
            if (target(i, j) > 0.5) {   // assumes target is one-hot encoded
                loss -= std::log(std::max(pred(i, j), epsilon));
            }
        }
    }
    this->lastCalculatedLoss = loss / pred.getRows();
    return this->lastCalculatedLoss;
}


Matrix CatCrossEntropy::calcGrad(const Matrix& pred, const Matrix& target) const {
    Matrix grad(pred.getRows(), pred.getCols());
    double epsilon = 1.0e-12; // small value to avoid division by 0

    for (int i = 0; i < pred.getRows(); i++) {
        for (int j = 0; j < pred.getCols(); j++) {
            grad(i, j) = pred(i, j) - target(i, j); // cross-entropy derivative for softmax is (pred - target)
        }
    }
    return grad.multScalar(1.0 / pred.getRows());
}

double CatCrossEntropy::getLastCalculatedLoss() const {
    return this->lastCalculatedLoss;
}