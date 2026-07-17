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

        inline static const double DEF_LR = 0.01;
        inline static const int DEF_EPOCHS = 1111;
        ~NeuralNetwork();
        NeuralNetwork(ILoss* loss);
        void addLayer(ILayer* layer);
        void train(const Matrix& input, const Matrix& target, int epochs = DEF_EPOCHS, double lr = DEF_LR, bool printProgress = false);
        Matrix predict(const Matrix& input) const;
        void setLossFunction(ILoss* newLoss);
};