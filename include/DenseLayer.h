#pragma once
#include "ILayer.h"
#include "IActivation.h"
#include "Matrix.h"
#include <fstream>

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
        Matrix forwardconst(const Matrix& input) const override;
        Matrix backward(const Matrix& outputGrad) override;
        void updateWeights(double learningRate) override;

        const Matrix& getWeights() const override;
        const Matrix& getBiases() const override;

        void save(std::ofstream& out) const override;
        void load(std::ifstream& in) override;
};