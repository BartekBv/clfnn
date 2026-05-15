#pragma once
#include "Matrix.h"

class IActivation {
    public:
        virtual ~IActivation() = default;
        virtual Matrix compute(const Matrix& input) const = 0; // = 0 mowi ze metoda musi byc zaimplementowana w klasie dziedziczacej
        virtual Matrix derivative(const Matrix& input) const = 0;
};