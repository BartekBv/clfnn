#pragma once
#include<stdexcept>
#include<vector>
#include<fstream>

/**
 * @brief Class representing a two-dimensional matrix of data.
 * Stores values in an std::vector structure and implements linear algebra operations.
 * Serves as the computational foundation for forward and backward propagation algorithms.
 */

class Matrix {
    private:
        std::vector<std::vector<double>> data;
        int rows;
        int cols;

    public:
        Matrix(int rows, int cols);

        [[nodiscard]] Matrix add(const Matrix& other) const;
        [[nodiscard]] Matrix dot(const Matrix& other) const;
        [[nodiscard]] Matrix subtract(const Matrix& other) const;
        [[nodiscard]] Matrix multScalar(double scalar) const;
        [[nodiscard]] Matrix multHadamard(const Matrix& other) const;
        [[nodiscard]] Matrix addBias(const Matrix& bias) const;
        [[nodiscard]] Matrix transpose() const;

        int getRows() const;
        int getCols() const;

        double& operator()(int row, int col);
        const double& operator()(int row, int col) const;

        void print() const;

        void save(std::ofstream& out) const;
        void load(std::ifstream& in);
};