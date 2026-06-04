#include "../include/NeuralNetwork.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(ILoss* loss) : lossFunction(loss) {}

NeuralNetwork::~NeuralNetwork() {
    for (ILayer* layer : layers) {
        delete layer;
    }
    delete lossFunction;
}

void NeuralNetwork::addLayer(ILayer* layer) {
    this->layers.push_back(layer);
}

void NeuralNetwork::train(const Matrix& input, const Matrix& target, int epochs, double lr) {
    for (int e = 0; e < epochs; e++) {
        Matrix current = input;
        for (ILayer* layer : layers) {
            current = layer->forward(current);
        }

        double currentLoss = this->lossFunction->calcLoss(current, target);

        Matrix grad = this->lossFunction->calcGrad(current, target);

        for (auto i = layers.rbegin(); i != layers.rend(); i++) {
            grad = (*i)->backward(grad);
        }

        for(ILayer* layer : layers) {
            layer->updateWeights(lr);
        }

        if (e % 100 == 0 || e == epochs - 1) {
            std::cout << "Epoch: " << e << ", Loss: " << currentLoss << "\n";
        }
    }
}