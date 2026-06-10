#pragma once
#include <string>
#include "Matrix.h"


class DataLoader {
    private:
        std::string filepath;
        int inputCols;
        int targetCols;
    
    public:
        DataLoader(const std::string& path, int incols, int outcols);
        Matrix loadInputs() const;
        Matrix loadTargets() const;
};