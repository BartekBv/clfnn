#include "../include/NeuralNetwork.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(ILoss* loss) : lossFunction(loss) {}