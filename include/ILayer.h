#pragma once
#include "Matrix.h"

class ILayer {
    public:
        virtual ~ILayer() = default;
        virtual Matrix forward(const Matrix& input) const = 0;
        virtual Matrix backward(const Matrix& gradOutput) const = 0;

        virtual Matrix getWeights() const = 0;
        virtual Matrix getBiases() const = 0;
};