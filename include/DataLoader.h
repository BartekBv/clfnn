#pragma once
#include <filesystem>
#include "Matrix.h"

/**
 * @brief Class responsible for loading datasets from a file.
 * Reads the file contents and splits them into an input feature matrix (inputs)
 * and an expected value matrix (targets) based on the given number of columns.
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