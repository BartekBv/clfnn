#pragma once
#include "ILayer.h"
#include "ILoss.h"
#include "Matrix.h"
#include <filesystem>
#include <vector>

/**
 * @brief This class manages the model's lifecycle: it stores the list of dense layers (DenseLayer)
 * and drives the prediction (predict) and training (train) processes.
 * Uses an externally injected loss function to evaluate prediction quality.
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

        void saveModel(const std::filesystem::path& filepath) const;
        void loadModel(const std::filesystem::path& filepath);
};