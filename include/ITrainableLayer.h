#pragma once
#include "Matrix.h"

/**
 * @brief Interface for layers that have learnable parameters.
 * Defines the operations needed to update weights and biases during training
 * and to inspect their current values. Only layers with trainable parameters
 * (e.g. `DenseLayer`) need to implement this, keeping parameterless layers
 * free of unused method implementations.
 */

class ITrainableLayer {
    public:
        virtual ~ITrainableLayer() = default;
        virtual void updateWeights(double learningRate) = 0;

        virtual const Matrix& getWeights() const = 0;
        virtual const Matrix& getBiases() const = 0;
};
