#include "../include/Matrix.h"
#include <iostream>
#include <iomanip>

Matrix::Matrix(int r, int c) : rows(r) , cols(c) {
    data.resize(r, std::vector<double>(c, 0.0));
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }

double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return data[row][col];
}

const double& Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return data[row][col];
}

Matrix Matrix::add(const Matrix& other) const {
    if(this->rows != other.rows || this->cols != other.cols){
        throw std::invalid_argument("Matrices must have the same dimensions in order to be added");
    }

    Matrix res(this->rows, this->cols);
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            res(i, j) = (*this)(i, j) + other(i, j);
        } 
    }

    return res;
}

Matrix Matrix::mult(const Matrix& other) const {
    if(this->cols != other.rows){
        throw std::invalid_argument("Incompatible dimensions for multiplication");
    }

    Matrix res(this->rows, other.cols);
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < other.cols; j++) {
            double sum = 0.0;
            for(int k = 0; k < this->cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            res(i, j) = sum;
        }
    }
    return res;
}

Matrix Matrix::transpose() const {
    Matrix res(this->cols, this->rows);
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) {
            res(j, i) = (*this)(i, j);
        }
    }
    return res;
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < cols; j++) {
            std::cout << std::fixed << std::setprecision(3) << (*this)(i, j) << " ";
        }
        std::cout << "]" << std::endl;
    }
}