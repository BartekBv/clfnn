#pragma once
#include "Matrix.h"

/**
 * @brief Interfejs dla funkcji straty.
 * Definiuje metody do obliczania wartości błędu pomiędzy predykcją a rzeczywistą wartością,
 * wyliczania gradientu niezbędnego do wstecznej propagacji oraz zwracania ostatnio obliczonej wartości straty.
 */

class ILoss {
    public:
        virtual ~ILoss() = default;
        virtual std::string getName() const = 0;
        virtual double calcLoss(const Matrix& predicted, const Matrix& target) const = 0;
        virtual Matrix calcGrad(const Matrix& predicted, const Matrix& target) const = 0;
        virtual double getLastCalculatedLoss() const = 0;
};