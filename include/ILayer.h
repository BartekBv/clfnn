#pragma once
#include "Matrix.h"

/**
 * @brief Interface for neural network layers.
 * Defines the core operations every layer must support: forward propagation
 * (stateful, for training, and stateless, for inference) and backward propagation.
 * Layers with learnable parameters or persistence needs implement the
 * additional `ITrainableLayer`/`IPersistableLayer` interfaces.
 */

class ILayer {
    public:
        virtual ~ILayer() = default;
        virtual Matrix forward(const Matrix& input) = 0;
        virtual Matrix forwardconst(const Matrix& input) const = 0;
        virtual Matrix backward(const Matrix& gradOutput) = 0;
};