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
        Matrix transpose() const;

        int getRows() const;
        int getCols() const;

        double& operator()(int row, int col);
        const double& operator()(int row, int col) const;

        void print() const;
};