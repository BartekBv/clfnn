#pragma once
#include "ILayer.h"
#include "IActivation.h"
#include "Matrix.h"

/**
 * @brief Warstwa w pełni połączona sieci neuronowej.
 * Przechowuje macierze wag i biasów oraz stany pośrednie na potrzeby propagacji wstecznej.
 * Wykonuje podanie danych w przód (z wykorzystaniem podanej funkcji aktywacji) i wstecz. Odpowiada za aktualizację wag i biasów na podstawie obliczonych gradientów. 
 */

class DenseLayer : public ILayer {
    private:
        Matrix weights;
        Matrix biases;
        Matrix lastInput;
        Matrix lastZ;
        Matrix current_dW;
        Matrix current_db;

        IActivation* activation;
    
    public:
        DenseLayer(int inputSize, int outputSize, IActivation* activation);
        ~DenseLayer() override;

        Matrix forward(const Matrix& input) override;
        Matrix backward(const Matrix& outputGrad) override;
        void updateWeights(double learningRate) override;

        Matrix getWeights() const override;
        Matrix getBiases() const override;
};