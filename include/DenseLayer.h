#pragma once
#include "ILayer.h"
#include "ITrainableLayer.h"
#include "IPersistableLayer.h"
#include "IActivation.h"
#include "Matrix.h"
#include <fstream>

/**
 * @brief Fully connected layer of a neural network.
 * Stores the weight and bias matrices along with intermediate states needed for backpropagation.
 * Performs forward propagation (using the given activation function) and backward propagation. Responsible for updating weights and biases based on the computed gradients.
 */

class DenseLayer : public ILayer, public ITrainableLayer, public IPersistableLayer {
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