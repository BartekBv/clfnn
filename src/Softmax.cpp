#include "../include/Softmax.h"
#include <cmath>


Matrix Softmax::compute(const Matrix& input) const {
    Matrix result(input.getRows(), input.getCols());

    for (int i = 0; i < input.getRows(); i++) {

        double maxi = input(i, 0);
        for (int j = 1;  j < input.getCols(); j++) {
            if (input(i, j) > maxi) {
                maxi = input(i, j);
            }
        }

        double sumexp = 0.0;
        for (int j = 0; j < input.getCols(); j++) {
            result(i, j) = std::exp(input(i, j) - maxi);
            sumexp += result(i, j);
        }

        for (int j = 0; j < input.getCols(); j++) {
            result(i, j) /= sumexp;
        }
    }
    return result;
}