#pragma once
#include <string>
#include <filesystem>
#include "Matrix.h"

/**
 * @brief Klasa odpowiedzialna za wczytywanie zestawów danych z pliku.
 * Odczytuje zawartość pliku i rozdziela ją na macierz cech wejściowych (inputs) 
 * oraz macierz wartości oczekiwanych (targets) na podstawie podanej liczby kolumn.
 */

class DataLoader {
    private:
        std::filesystem::path filepath;
        int inputCols;
        int targetCols;
    
    public:
        DataLoader(const std::filesystem::path& path, int incols, int outcols);
        Matrix loadInputs() const;
        Matrix loadTargets() const;
};