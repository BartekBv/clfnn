#include "../include/NeuralNetwork.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include<stdexcept>

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

void NeuralNetwork::train(const Matrix& input, const Matrix& target, int epochs, double lr, bool printProgress) {
    for (int e = 0; e < epochs; e++) {
        Matrix current = input;
        for (ILayer* layer : layers) {
            current = layer->forward(current);
        }

        double currentLoss = this->lossFunction->calcLoss(current, target);
        if(currentLoss < 1e-6) {
            if(printProgress) {
                std::cout << "Early stopping at epoch " << e << " with loss: " << currentLoss << "\n";
            }
            break;
        }

        Matrix grad = this->lossFunction->calcGrad(current, target);

        for (auto i = layers.rbegin(); i != layers.rend(); i++) {
            grad = (*i)->backward(grad);
        }

        for(ILayer* layer : layers) {
            layer->updateWeights(lr);
        }

        if (printProgress && (e % 500 == 0 || e == epochs - 1)) {
            std::cout << "Epoch [ "
                      << std::setw(std::to_string(epochs).length()) << e
                      << " / " << epochs - 1 << " ]  Loss: " 
                      << std::fixed << std::setprecision(6) << currentLoss << "\n";
        }
    }
}

Matrix NeuralNetwork::predict(const Matrix& input) const {
    Matrix current = input;

    for (ILayer* layer : layers) {
        current = layer->forwardconst(current);
    }

    return current;
}

void NeuralNetwork::setLossFunction(ILoss* newLoss) {
    delete this->lossFunction;
    this->lossFunction = newLoss;
}



void NeuralNetwork::saveModel(const std::filesystem::path& filepath) const {
    std::ofstream out(filepath, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Nie można otworzyć pliku do zapisu modelu.");
    }

    for (const auto& layer : layers) {
        layer->save(out);
    }
    
    out.close();
}

void NeuralNetwork::loadModel(const std::filesystem::path& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Nie można otworzyć pliku do odczytu modelu.");
    }

    for (const auto& layer : layers) {
        layer->load(in);
    }
    
    in.close();
}