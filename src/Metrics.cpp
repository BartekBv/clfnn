#include "../include/Metrics.h"

double Metrics::accuracy(const Matrix& pred, const Matrix& target) {
    int correct = 0;
    int predictions = pred.getRows();

    for(int i = 0; i < predictions; i++) {
        int predClass = argmax(pred, i);
        int trueClass = argmax(target, i);

        if(predClass == trueClass) {
            correct++;
        }
    }
    return (double)correct / predictions * 100.0;
}

int Metrics::argmax(const Matrix& matrix, int row) {
    int mId = 0;
    double mVal = matrix(row, 0);
    for(int j = 1; j < matrix.getCols(); j++) {
        if(matrix(row, j) > mVal) {
            mVal = matrix(row, j);
            mId = j;
        }
    }
    return mId;
}