#include "../include/DenseLayer.h"
#include <cstdlib> // for rand() and RAND_MAX
#include <stdexcept>

DenseLayer::DenseLayer(int inputSize, int outputSize, IActivation* activation)
    : weights(inputSize, outputSize), biases(1, outputSize),
      lastInput(1, 1), lastZ(1, 1),
      current_dW(inputSize, outputSize), current_db(1, outputSize),
      activation(activation) 
{
        for (int i = 0; i < inputSize; i++){
            for (int j = 0; j < outputSize; j++){
                weights(i, j) = ((double)rand() / RAND_MAX) - 0.5;
                //random weights in the range [-0.5, 0.5]
            }
        }

        for(int i = 0; i < outputSize; i++){
            biases(0, i) = 0.0;
        }
}

DenseLayer::~DenseLayer() {
    delete this->activation;
}

Matrix DenseLayer::forward(const Matrix& input) {
    this->lastInput = input;
    this->lastZ = input.dot(weights).addBias(biases);
    return this->activation->compute(this->lastZ);
}

Matrix DenseLayer::forwardconst(const Matrix& input) const {
    Matrix z = input.dot(weights).addBias(biases);
    return this->activation->compute(z);
}

Matrix DenseLayer::backward(const Matrix& outputGrad) {
    Matrix dZ = outputGrad.multHadamard(this->activation->derivative(this->lastZ));

    this->current_dW = this->lastInput.transpose().dot(dZ);

    for(int j = 0; j < this->biases.getCols(); j++) {
        double sum = 0.0;
        for(int i = 0; i < dZ.getRows(); i++) {
            sum += dZ(i, j);
        }
        this->current_db(0, j) = sum;
    }

    return dZ.dot(this->weights.transpose());
}

void DenseLayer::updateWeights(double learningRate) {
    this->weights = this->weights.subtract(this->current_dW.multScalar(learningRate));
    this->biases = this->biases.subtract(this->current_db.multScalar(learningRate));
}

const Matrix& DenseLayer::getWeights() const {
    return this->weights;
}

const Matrix& DenseLayer::getBiases() const {
    return this->biases;
}

void DenseLayer::save(std::ofstream& out) const {
    weights.save(out);
    biases.save(out);
}

void DenseLayer::load(std::ifstream& in) {
    Matrix newWeights(1, 1);
    Matrix newBiases(1, 1);
    newWeights.load(in);
    newBiases.load(in);

    if (newWeights.getRows() != weights.getRows() || newWeights.getCols() != weights.getCols() || newBiases.getRows() != biases.getRows() || newBiases.getCols() != biases.getCols()) {
        throw std::runtime_error("Layer dimensions in the model file do not match the current network architecture.");
    }

    weights = newWeights;
    biases = newBiases;
}
