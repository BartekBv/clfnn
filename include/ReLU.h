#pragma once
#include "IActivation.h"

/**
 * @brief Implementacja funkcji aktywacji Leaky ReLU.
 * Dla wartości dodatnich zwraca wartość wejściową, a dla ujemnych wartość przemnożoną przez współczynnik alpha.
 * Oblicza również pochodną, która jest potrzebna do propagacji wstecznej.
 */

class ReLU : public IActivation {
    private:
        double alpha; //leaky ReLU parameter

    public:
        explicit ReLU(double alpha = 0.01);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};