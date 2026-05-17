#include "../include/ReLU.h"
#include <algorithm>

Matrix ReLU::compute(const Matrix& input) const {
    Matrix res(input.getRows(), input.getCols());

    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getCols(); j++) {
            res(i, j) = std::max(0.0, input(i, j));
        }
    }

    return res;
}

Matrix ReLU::derivative(const Matrix& input) const {
    Matrix res(input.getRows(), input.getCols());

    for (int i = 0; i < input.getRows(); i++) {
        for (int j = 0; j < input.getCols(); j++) {
            res(i, j) = input(i, j) > 0.0 ? 1.0 : 0.0;
        }
    }
    
    return res;
}