#pragma once
#include "Matrix.h"
#include <fstream>

/**
 * @brief Interfejs dla warstw sieci neuronowej.
 * Definiuje podstawowe operacje: propagację w przód, propagację wstecz
 * oraz aktualizację parametrów (wag i biasów).
 */

class ILayer {
    public:
        virtual ~ILayer() = default;
        virtual Matrix forward(const Matrix& input) = 0;
        virtual Matrix forwardconst(const Matrix& input) const = 0;
        virtual Matrix backward(const Matrix& gradOutput) = 0;
        virtual void updateWeights(double learningRate) = 0;

        virtual const Matrix& getWeights() const = 0;
        virtual const Matrix& getBiases() const = 0;

        virtual void save(std::ofstream& out) const = 0;
        virtual void load(std::ifstream& in) = 0;
};