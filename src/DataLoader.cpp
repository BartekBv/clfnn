#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string_view>
#include <charconv>


DataLoader::DataLoader(const std::filesystem::path& path, int incols, int tarcols)
    : filepath(path), inputCols(incols), targetCols(tarcols) {}

Matrix DataLoader::loadInputs() const {
    if (!std::filesystem::exists(this->filepath)) {
        throw std::runtime_error("Error: File not found: " + this->filepath.string());
    }

    if(!std::filesystem::is_regular_file(this->filepath)) {
        throw std::runtime_error("Error: Path is not a regular file: " + this->filepath.string());
    }

    std::ifstream file(this->filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + this->filepath.string());
    }

    std::vector<std::vector<double>> inputData;
    std::string line;

    while(std::getline(file, line)) {
        if(line.empty()) continue;

        std::vector<double> row;

        std::string_view lineView(line);
        size_t start = 0;
        size_t end = lineView.find(',');
        int colId = 0;

        while(start <= lineView.size()){
            std::string_view valView = lineView.substr(start, end - start);
            
            if(colId < this->inputCols){
                double value = 0.0;
                auto [ptr, ec] = std::from_chars(valView.data(), valView.data() + valView.size(), value);

                if(ec == std::errc()){
                    row.push_back(value);
                } else{
                    throw std::runtime_error("Error: Invalid input value: " + std::string(valView) + " in file: " + this->filepath.string());
                }
            }

            if(end == std::string_view::npos) break;
            
            start = end + 1;
            end = lineView.find(',', start);
            colId++;
        }

        if(row.size() == this->inputCols) {
            inputData.push_back(row);
        } else if (!row.empty()) {
            throw std::runtime_error("Error: Expected " + std::to_string(this->inputCols) + " input columns, but got " + std::to_string(row.size()) + " in file: " + this->filepath.string());
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
    if (!std::filesystem::exists(this->filepath)) {
        throw std::runtime_error("Error: File not found: " + this->filepath.string());
    }

    if(!std::filesystem::is_regular_file(this->filepath)) {
        throw std::runtime_error("Error: Path is not a regular file: " + this->filepath.string());
    }

    std::ifstream file(this->filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Cannot open file " + this->filepath.string());
    }

    std::vector<std::vector<double>> targetData;
    std::string line;

    while(std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<double> row;
        std::string_view lineView(line);
        
        size_t start = 0;
        size_t end = lineView.find(',');
        int colId = 0;

        while (start <= lineView.length()) {
            std::string_view valView = lineView.substr(start, end - start);
            
            if(colId >= this->inputCols && colId < (this->inputCols + this->targetCols)){
                double value = 0.0;
                auto [ptr, ec] = std::from_chars(valView.data(), valView.data() + valView.size(), value);
                
                if (ec == std::errc()) {
                    row.push_back(value);
                } else {
                    throw std::runtime_error("Error: Invalid target value in file: " + this->filepath.string());
                }
            }
            
            if (end == std::string_view::npos) break;
            
            start = end + 1;
            end = lineView.find(',', start);
            colId++;
        }

        if(row.size() == this->targetCols) {
            targetData.push_back(row);
        } else if (!row.empty()) {
            throw std::runtime_error("Error: Expected " + std::to_string(this->targetCols) + " target columns, but got " + std::to_string(row.size()) + " in file: " + this->filepath.string());
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