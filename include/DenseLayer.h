#pragma once
#include "ILayer.h"
#include "IActivation.h"
#include "Matrix.h"

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

        Matrix forward(const Matrix& input) override;
        Matrix backward(const Matrix& outputGrad) override;
        void updateWeights(double learningRate) override;

        Matrix getWeights() const override;
        Matrix getBiases() const override;
};