#include "../include/DenseLayer.h"
#include <cstdlib> // for rand() and RAND_MAX

DenseLayer::DenseLayer(int inputSize, int outputSize, IActivation* activation)
    : weights(inputSize, outputSize), biases(1, outputSize),
      lastInput(1, 1), lastZ(1, 1),
      current_dW(inputSize, outputSize), current_db(1, outputSize),
      activation(activation) 
{
        for (int i = 0; i < inputSize; i++){
            for (int j = 0; j < outputSize; j++){
                weights(i, j) = (double)rand() / RAND_MAX) - 0.5;
                //losowe wagi z zakresu [-0.5, 0.5]
            }
        }

        for(int i = 0; i < outputSize; i++){
            biases(0, i) = 0.0;
        }
}

Matrix DenseLayer::forward(const Matrix& input) {
    this->lastInput = input;
    this->lastZ = input.dot(weights).addBias(biases);
    return this->activation->compute(this->lastZ);
}

Matrix DenseLayer::backward(const Matrix& outputGrad) {
    Matrix dZ = outputGrad.multHadamard(this->activation->derivatrive(this->lastZ));

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