#pragma once
#include "IActivation.h"

/**
 * @brief Implementacja funkcji aktywacji Sigmoid.
 * Mapuje wartości wejściowe na przedział (0, 1). Opcjonalny parametr steepness pozwala na modyfikację nachylenia krzywej.
 * Oblicza również pochodną, która jest potrzebna do propagacji wstecznej.
 */

class Sigmoid : public IActivation {
    private:
        double steepness;

    public:
        explicit Sigmoid(double steepness = 1.0);
        Matrix compute(const Matrix& input) const override;
        Matrix derivative(const Matrix& input) const override;
};