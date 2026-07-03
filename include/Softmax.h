#pragma once
#include "IActivation.h"
#include "Matrix.h"

/**
 * @brief Implementacja funkcji aktywacji Softmax.
 * Normalizuje wartości wejściowe do postaci rozkładu prawdopodobieństwa sumującego się do 1. 
 * Metoda pochodnej jest zoptymalizowana do bezpośredniej współpracy z kategoryczną entropią krzyżową.
 */

class Softmax : public IActivation {
    public:
        Softmax() = default;
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};