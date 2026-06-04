#include "../include/NeuralNetwork.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(ILoss* loss) : lossFunction(loss) {}

NeuralNetwork::~NeuralNetwork() {
    for (ILayer* layer : layers) {
        delete layer;
    }
    delete lossFunction;
}