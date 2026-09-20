#pragma once
#include "Matrix.h"

/**
 * @brief A collection of static methods for evaluating model prediction quality.
 * Provides metrics that compare the network's output with the actual labels.
 * Used to evaluate the model after training.
 */

class Metrics {
    public:
        static double accuracy(const Matrix& pred, const Matrix& target);
    
    private:
        static int argmax(const Matrix& matrix, int row);
};