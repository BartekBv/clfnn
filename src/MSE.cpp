#include "../include/MSE.h"
#include <stdexcept>

double MSE::calcLoss(const Matrix& pred, const Matrix& target) const {
    if (pred.getRows() != target.getRows() || pred.getCols() != target.getCols()) {
        throw std::invalid_argument("Predicted and target matrices must have the same dimensions.");
    }

    double sum = 0.0;

    for (int i = 0; i < pred.getRows(); i++) {
        for (int j = 0; j < pred.getCols(); j++) {
            double diff = pred(i, j) - target(i, j);
            sum += diff * diff;
        }
    }

    return sum / (pred.getRows() * pred.getCols());
}


Matrix MSE::calcGrad(const Matrix& pred, const Matrix& target) const {
    if(pred.getRows() != target.getRows() || pred.getCols() != target.getCols()) {
        throw std::invalid_argument("Predicted and target matrices must have the same dimensions.");
    }

    int r = pred.getRows();
    int c = pred.getCols();
    int n = r * c;
    Matrix grad(r, c);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            grad(i, j) = 2.0 * (pred(i, j) - target(i, j)) / n;
        }
    }

    return grad;
}