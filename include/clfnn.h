#pragma once
#include "DataLoader.h"
#include "NeuralNetwork.h"
#include "DenseLayer.h"
#include "Sigmoid.h"
#include "MSE.h"
#include "ReLU.h"
#include "Softmax.h"
#include "CatCrossEntropy.h"


/**
 * @brief Umbrella header for the CLFNN library.
 * Includes all the components needed to build,
 * train, and evaluate a neural network,
 * allowing the library to be used via a single #include "clfnn.h".
 * Also defines helper ANSI color codes for formatting console output.
 */

namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";
    const std::string PURPLE  = "\033[35m";
    const std::string BLUE    = "\033[34m";
}