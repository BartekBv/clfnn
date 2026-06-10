#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>


DataLoader::DataLoader(const std::string& path, int incols, int tarcols)
    : filepath(path), inputCols(incols), targetCols(tarcols) {}

Matrix DataLoader::loadInputs() const {
    std::ifstream file(this->filepath);
    if (!file.is_open()) {
        std::cerr << "Error in opening file: " << this->filepath << std::endl;
        return Matrix(0, 0);
    }

    std::vector<std::vector<double>> inputData;
    std::string line;

    while(std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string val;
        int colId = 0;

        while (std::getline(ss, val, ',')) {
            if(colId < this->inputCols){
                try {
                    row.push_back(std::stod(val));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid input value: " << val << " in file: " << this->filepath << std::endl;
                    row.push_back(0.0);
                }catch (const std::out_of_range& e) {
                    std::cerr << "Input value out of range: " << val << " in file: " << this->filepath << std::endl;
                    row.push_back(0.0);
                }
            }
            colId++;
        }
        if(row.size() == this->inputCols) {
            inputData.push_back(row);
        } else if (!row.empty()) {
            std::cerr << "Warning: Expected " << this->inputCols << " input columns, but got " << row.size() << " in file: " << this->filepath << std::endl;
        }
    }
    file.close();

    Matrix result(inputData.size(), this->inputCols);
    for (size_t i = 0; i < inputData.size(); i++) {
        for (int j = 0; j < this->inputCols; j++) {
            result(i, j) = inputData[i][j];
        }
    }
    return result;
}

Matrix DataLoader::loadTargets() const {
    std::ifstream file(this->filepath);
    if (!file.is_open()) {
        std::cerr << "Error in opening file: " << this->filepath << std::endl;
        return Matrix(0, 0);
    }

    std::vector<std::vector<double>> targetData;
    std::string line;

    while(std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string val;
        int colId = 0;

        while (std::getline(ss, val, ',')) {
            if(colId >=this->inputCols && colId < (this->inputCols + this->targetCols)){
                try {
                    row.push_back(std::stod(val));
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid target value: " << val << " in file: " << this->filepath << std::endl;
                    row.push_back(0.0);
                }catch (const std::out_of_range& e) {
                    std::cerr << "Target value out of range: " << val << " in file: " << this->filepath << std::endl;
                    row.push_back(0.0);
                }
            }
            colId++;
        }
        if(row.size() == this->targetCols) {
            targetData.push_back(row);
        } else if (!row.empty()) {
            std::cerr << "Warning: Expected " << this->targetCols << " target columns, but got " << row.size() << " in file: " << this->filepath << std::endl;
        }
    }
    file.close();

    Matrix result(targetData.size(), this->targetCols);
    for (size_t i = 0; i < targetData.size(); i++) {
        for (int j = 0; j < this->targetCols; j++) {
            result(i, j) = targetData[i][j];
        }
    }
    return result;
}