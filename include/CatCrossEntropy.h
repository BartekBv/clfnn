#pragma once
#include "ILoss.h"

/**
 * @brief Implementacja funkcji straty kategorycznej entropii krzyżowej (Categorical Cross-Entropy).
 * Służy do oceny błędu predykcji w problemach klasyfikacji wieloklasowej. 
 * Przeznaczona do bezpośredniej współpracy z funkcją aktywacji Softmax.
 * Oblicza wartość straty na podstawie przewidywanych prawdopodobieństw i rzeczywistych etykiet, a także gradient potrzebny do propagacji wstecznej.
 * Przechowuje ostatnio obliczoną wartość straty, która może być zwrócona przez metodę getLastCalculatedLoss().
 * Metoda getName() zwraca skrót "CCE".
 */

class CatCrossEntropy : public ILoss {
    private:
        mutable double lastCalculatedLoss = 0.0;

    public:
        std::string getName() const override { return "CCE"; }
        double calcLoss(const Matrix& pred, const Matrix& target) const override;
        Matrix calcGrad(const Matrix& pred, const Matrix& target) const override;
        double getLastCalculatedLoss() const override;
};