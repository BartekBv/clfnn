#pragma once
#include "Matrix.h"

/**
 * @brief Zbiór statycznych metod do oceny jakości predykcji modelu.
 * Udostępnia metryki porównujące wyjście sieci z rzeczywistymi etykietami.
 * Wykorzystywane do ewaluacji modelu po treningu.
 */

class Metrics {
    public:
        static double accuracy(const Matrix& pred, const Matrix& target);
    
    private:
        static int argmax(const Matrix& matrix, int row);
};