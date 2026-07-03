#pragma once
#include "ILoss.h"

/**
 * @brief Implementacja funkcji straty błędu średniokwadratowego (Mean Squared Error).
 * Oblicza średnią z kwadratów różnic między predykcją a oczekiwaną wartością. 
 * Oblicza również gradient, który jest potrzebny do propagacji wstecznej. Przechowuje ostatnio obliczoną wartość straty, która może być zwrócona przez metodę getLastCalculatedLoss(). Metoda getName() zwraca skrót "MSE".
 */

class MSE : public ILoss {
    private:
        mutable double lastCalculatedLoss = 0.0;
        
    public:
        std::string getName() const override { return "MSE"; }
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
        double getLastCalculatedLoss() const override;
};