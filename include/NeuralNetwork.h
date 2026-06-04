#pragma once
#include "ILayer.h"
#include "ILoss.h"
#include "Matrix.h"
#include <vector>

class NeuralNetwork {
    private:
        std::vector<ILayer*> layers;
        ILoss* lossFunction;
    
    public:
        ~NeuralNetwork();
        NeuralNetwork(ILoss* loss);
        void addLayer(ILayer* layer);
        void train(const Matrix& input, const Matrix& target, int epochs, double lr);
        const Matrix predict(const Matrix& input);
};