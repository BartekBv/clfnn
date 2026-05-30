#pragma once
#include<stdexcept>
#include<vector>

class Matrix {
    private:
        std::vector<std::vector<double>> data;
        int rows;
        int cols;

    public:
        Matrix(int rows, int cols);

        Matrix add(const Matrix& other) const;
        Matrix dot(const Matrix& other) const;
        Matrix subtract(const Matrix& other) const;
        Matrix multScalar(double scalar) const;
        Matrix multHadamard(const Matrix& other) const;
        Matrix addBias(const Matrix& bias) const;
        Matrix transpose() const;

        int getRows() const;
        int getCols() const;

        double& operator()(int row, int col);
        const double& operator()(int row, int col) const;

        void print() const;
};