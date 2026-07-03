#pragma once
#include "Matrix.h"

class Metrics {
    public:
        static double accuracy(const Matrix& pred, const Matrix& target);
    
    private:
        static int argmax(const Matrix& matrix, int row);
};