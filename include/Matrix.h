#pragma once
#include<stdexcept>
#include<vector>

/**
 * @brief Klasa reprezentująca dwuwymiarową macierz danych.
 * Przechowuje wartości w strukturze std::vector i realizuje operacje algebry liniowej. 
 * Stanowi podstawę obliczeniową dla algorytmów propagacji w przód oraz propagacji wstecznej.
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
};