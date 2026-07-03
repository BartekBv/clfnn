#pragma once
#include "Matrix.h"

/**
 * @brief Interfejs dla warstw sieci neuronowej.
 * Definiuje podstawowe operacje: propagację w przód, propagację wstecz
 * oraz aktualizację parametrów (wag i biasów).
 */

class ILayer {
    public:
        virtual ~ILayer() = default;
        virtual Matrix forward(const Matrix& input) = 0;
        virtual Matrix backward(const Matrix& gradOutput) = 0;
        virtual void updateWeights(double learningRate) = 0;

        virtual Matrix getWeights() const = 0;
        virtual Matrix getBiases() const = 0;
};