#include "../include/Sigmoid.h"
#include <cmath>

Sigmoid::Sigmoid(double steepness) : steepness(steepness) {}

Matrix Sigmoid::compute(const Matrix& input) const {
    Matrix res(input.getRows(), input.getCols());

    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getCols(); j++){
            res(i, j) = 1.0 / (1.0 + std::exp(-this->steepness * input(i, j)));
        }
    }

    return res;
}

Matrix Sigmoid::derivative(const Matrix& input) const {
    Matrix res(input.getRows(), input.getCols());

    //pochodna sigmoid(x) = (steepness) * sigmoid(x) * (1 - sigmoid(x))
    Matrix sigval = compute(input);
    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getCols(); j++){
            res(i, j) = this->steepness * sigval(i, j) * (1.0 - sigval(i, j));
        }
    }

    return res;
}