#include "clfnn.h"
#include "Metrics.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

void printIrisTable(const Matrix& inputs, const Matrix& predictions, const Matrix& targets) {
    std::cout << "\n";
    const int w = 10;
    const int w1= 18;
    std::string species[] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};
    int total = predictions.getRows();

    std::cout << Color::YELLOW
              << std::left << std::fixed << std::setprecision(4)
              << std::setw(w1) << "SepalLengthCm"
              << std::setw(w1) << "SepalWidthCm"
              << std::setw(w1) << "PetalLengthCm"
              << std::setw(w1) << "PetalWidthCm"
              << std::setw(w1) << "Species"
              << std::setw(w) << "P(set.)"
              << std::setw(w) << "P(vers.)"
              << std::setw(w) << "P(virg.)"
              << std::setw(w1) << "Prediction"
              << std::setw(w + 2) << "Confidence"
              << Color::RESET << "\n";

    std::cout << Color::CYAN << std::string(w * 4 + w1 * 6, '-') << Color::RESET << "\n";

    for(int i = 0; i < total; i++) {
        int predictedClass = 0; double maxProb = predictions(i, 0);
        for (int j = 1; j < predictions.getCols(); j++) {
            if (predictions(i, j) > maxProb) { maxProb = predictions(i, j); predictedClass = j; }
        }
        
        int trueClass = -1;
        for (int j = 0; j < targets.getCols(); j++) {
            if (targets(i, j) > 0.5) { trueClass = j; break; }
        }

        std::string rowColor = (predictedClass == trueClass) ? Color::GREEN : Color::RED;
        std::cout << std::left << std::fixed << std::setprecision(4)
                  << std::setw(w1) << inputs(i, 0)
                  << std::setw(w1) << inputs(i, 1)
                  << std::setw(w1) << inputs(i, 2)
                  << std::setw(w1) << inputs(i, 3)
                  << std::setw(w1) << species[trueClass]
                  << std::setw(w) << predictions(i, 0)
                  << std::setw(w) << predictions(i, 1)
                  << std::setw(w) << predictions(i, 2)
                  << rowColor << std::setw(w1) << species[predictedClass] << Color::RESET
                  << std::setw(w) << maxProb
                  << Color::RESET << "\n";
    }
    std::cout << Color::CYAN << std::string(w * 4 + w1 * 6, '-') << Color::RESET << "\n";
}

int main() {
    try {
        // Load training and testing data. Initialize loss and activaion functions, and set up the neural network. Then, train the network and evaluate its performance before and after training.
        DataLoader trainloader("utils/iris_train.csv", 4, 3);
        Matrix X_train = trainloader.loadInputs();
        Matrix Y_train = trainloader.loadTargets();

        DataLoader testloader("utils/iris_test.csv", 4, 3);
        Matrix X_test = testloader.loadInputs();
        Matrix Y_test = testloader.loadTargets();

        ILoss* cce = new CatCrossEntropy();
        Softmax* softmax = new Softmax();
        ReLU* relu = new ReLU();
        
        NeuralNetwork nn(cce);
        nn.addLayer(new DenseLayer(4, 8, relu));
        nn.addLayer(new DenseLayer(8, 3, softmax));

        Matrix predbefore = nn.predict(X_test);
        printIrisTable(X_test, predbefore, Y_test);
        
        double accuracyBefore = Metrics::accuracy(predbefore, Y_test);
        std::string accBeforeColor = (accuracyBefore > 90.0) ? Color::GREEN : Color::RED;
        std::cout << "Percentage of correct predictions before training: " 
                  << accBeforeColor << accuracyBefore << "%" 
                  << Color::RESET << "\n\n";

        std::cout << "Training: \n";
        nn.train(X_train, Y_train, 13000, 0.7, true); 

        Matrix predafter = nn.predict(X_test);
        printIrisTable(X_test, predafter, Y_test);
        
        double accuracyAfter = Metrics::accuracy(predafter, Y_test);
        std::string accAfterColor = (accuracyAfter > 90.0) ? Color::GREEN : Color::RED;
        std::cout << "\nPercentage of correct predictions after training: " 
                  << accAfterColor << accuracyAfter << "%" 
                  << Color::RESET << "\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}