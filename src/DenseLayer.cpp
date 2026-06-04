#include "../include/DenseLayer.h"

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
