#include "../include/NeuralNetwork.h"
#include "../include/ITrainableLayer.h"
#include "../include/IPersistableLayer.h"
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
            if (auto* trainable = dynamic_cast<ITrainableLayer*>(layer)) {
                trainable->updateWeights(lr);
            }
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
        throw std::runtime_error("Cannot open file for writing the model.");
    }

    size_t layercnt = layers.size();
    out.write(reinterpret_cast<const char*>(&layercnt), sizeof(layercnt));

    for (const auto& layer : layers) {
        if (auto* persistable = dynamic_cast<IPersistableLayer*>(layer)) {
            persistable->save(out);
        }
    }

    out.close();
}

void NeuralNetwork::loadModel(const std::filesystem::path& filepath) {
    std::ifstream in(filepath, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Cannot open file for reading the model.");
    }

    size_t layercnt = 0;
    in.read(reinterpret_cast<char*>(&layercnt), sizeof(layercnt));
    if (layercnt != layers.size()) {
        throw std::runtime_error("Number of layers in the file (" + std::to_string(layercnt) +") does not match the network architecture (expected " + std::to_string(layers.size()) + ").");
    }

    for (const auto& layer : layers) {
        if (auto* persistable = dynamic_cast<IPersistableLayer*>(layer)) {
            persistable->load(in);
        }
    }

    in.close();
}