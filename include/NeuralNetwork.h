#pragma once
#include "ILayer.h"
#include "ILoss.h"
#include "Matrix.h"
#include <vector>

/**
 * @brief Klasa ta zarządza cyklem życia modelu: przechowuje listę warstw gęstych (DenseLayer), 
 * inicjuje proces przewidywania (predict) oraz nauki (train).
 * Wykorzystuje wstrzykiwaną z zewnątrz funkcję straty, aby ocenić jakość predykcji.
 */

class NeuralNetwork {
    private:
        std::vector<ILayer*> layers;
        ILoss* lossFunction;
    
    public:
        ~NeuralNetwork();
        NeuralNetwork(ILoss* loss);
        void addLayer(ILayer* layer);
        void train(const Matrix& input, const Matrix& target, int epochs, double lr, bool printProgress = false);
        Matrix predict(const Matrix& input) const;
        void setLossFunction(ILoss* newLoss);
};