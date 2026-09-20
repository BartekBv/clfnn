# CLFNN

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C++-17%2B-blue.svg)

**C++ Library for Feedforward Neural Networks**

CLFNN is an object-oriented, multilayer perceptron library built completely from scratch. It relies solely on C++ standard library, featuring its own custom-built mathematical engine. It provides functionalities such as:
* loading data
* building custom dense layers
* training neural networks using gradient-descent with backpropagation
* applying trained model for both classification and regression tasks

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Documentation](#documentation)
- [Usage](#usage)
- [Example: Iris Classification](#example-iris-classification)
- [Architecture](#architecture)
- [License](#license)

## Features

- **Custom Matrix Engine**
  - Cache-optimized matrix multiplication.
  - Supports fundamental algebraic operations, transpositions, and Hadamard products.
- **Strictly Object-Oriented Design**
  - Seamless modularity via `ILayer`, `ILoss`, and `IActivation` interfaces.
- **Layers and Activations**
  - Fully configurable Dense Layers.
  - Available activation functions: `ReLU`, `Sigmoid`, `Softmax`.
- **Optimization and Loss**
  - Built-in error calculations for `MSE` (Mean Squared Error) and `CCE` (Categorical Cross-Entropy).
  - Full backpropagation algorithm with early stopping mechanisms.
- **Model Persistence**
  - Save and load trained models to/from binary files via `saveModel()`/`loadModel()`, with architecture validation on load.
- **Evaluation Metrics**
  - `Metrics::accuracy()` for quick classification accuracy scoring against one-hot encoded targets.

## Requirements

- **C++ Compiler**: Full C++17 support, including `<charconv>` floating-point parsing (`std::from_chars` for `double`), used by `DataLoader`. In practice: **GCC 11+**, **Clang 14+** (with a matching libc++), or **MSVC 19.24+** (Visual Studio 2019 16.4+). Earlier compilers may support the rest of C++17 but lack this specific library feature and will fail to compile.
- **Python** (Optional): For running the data preprocessing script.

## Installation

To install the library, simply clone the repository to your local machine.
```bash
git clone https://github.com/BartekBv/clfnn.git
cd clfnn
```

## Documentation

Full API reference (generated with Doxygen) is available at **[bartekbv.github.io/clfnn](https://bartekbv.github.io/clfnn/)**, automatically rebuilt from `include/` and `src/` on every push to `main`.

## Usage

### Include the header file
```C++
#include "clfnn.h"
```

### Compile your program
```bash
g++ -O3 your_main.cpp src/*.cpp -I include -o your_executable
```

### Example Code
Example of loading data, building network, training model and applying it for prediction:
```C++
#include "clfnn.h"

int main() {
    // Initialize the loss function along with neural net and create custom layers.
    //Then load data using built-in DataLoader, train the model and apply it.
    ILoss* cce = new CatCrossEntropy();
    NeuralNetwork nn(cce);

    nn.addLayer(new DenseLayer(4, 8, new ReLU()));
    nn.addLayer(new DenseLayer(8, 3, new Softmax()));

    DataLoader loader("data/iris.csv", 4, 3);
    Matrix X_train = loader.loadInputs();
    Matrix Y_train = loader.loadTargets();

    int epochs = 15000;
    double learning_rate = 0.1;
    bool print_progress = true;
    nn.train(X_train, Y_train, epochs, learning_rate, print_progress);

    Matrix predictions = nn.predict(X_train);

    return 0;
}
```

### Saving and Loading a Model
```C++
// Save the model to a binary file after training
// Next you may rebuild the same architecture, then load the saved weights
nn.saveModel("model.bin");

NeuralNetwork nn2(new CatCrossEntropy());
nn2.addLayer(new DenseLayer(4, 8, new ReLU()));
nn2.addLayer(new DenseLayer(8, 3, new Softmax()));
nn2.loadModel("model.bin");

Matrix predictions = nn2.predict(X_train);
```
`loadModel()` checks that the file's architecture (number of layers and their dimensions) matches the current network, and throws an exception on mismatch.

## Example: Iris Classification
This repository includes a classification example located in the `examples/` directory, built around the [Iris Species dataset](https://www.kaggle.com/datasets/uciml/iris). The program evaluates the model with random initial weights, executes the training process over 13,000 epochs, and re-evaluates the predictions to demonstrate model's accuracy improvement

### Data Preprocessing
The `Iris.csv` dataset was preprocessed using the Python scripts located in the `examples/data/` folder (`one_hot_iris.py`). Mentioned script applies One-Hot Encoding to target labels and splits the data into training and testing subsets.

### Compiling and Running the Demo
To execute the example directly from project's root directory, run:
```bash
g++ -O3 examples/example.cpp src/*.cpp -I include -o example_exec
./example_exec
```
### Output

![Terminal Execution](images/model_demo.png)


## Architecture

Library is built on Object-oriented programming principles. Such architecture achieves high modularity and maintainability.

### SOLID
* Single Responsibility: Classes have strictly bounded scopes (`Matrix` isolates linear algebra, `DataLoader` handles pure file I/O).
* Open/Closed Principle: Custom layers (e.g. `DropoutLayer`) or loss functions can be injected without altering the `NeuralNetwork`.
* Liskov Substitution Principle: Polymorphic design ensures subclasses (e.g. `ReLU`, `CatCrossEntropy`) can replace their abstract interfaces (`IActivation`, `ILoss`). (`Softmax` is one documented exception — its derivative is simplified to work only when paired with `CatCrossEntropy`; see their header comments.)
* Interface Segregation Principle: `ILayer` covers only the core operations every layer must support (`forward`, `forwardconst`, `backward`). Trainable parameters (`updateWeights`, `getWeights`, `getBiases`) and persistence (`save`, `load`) are split into separate `ITrainableLayer`/`IPersistableLayer` interfaces, so a parameterless layer (e.g. `DropoutLayer`) only needs to implement `ILayer`.
* Dependency Inversion Principle: The `NeuralNetwork` class does not instantiate its own layers or loss functions. Instead, it depends entirely on abstractions (`ILayer`, `ILoss`) injected via its constructor and methods, separating training loop from mathematical implementations.

![UML Diagram](images/diagram_klas.png)

### Performance
* Parsing: The `DataLoader` abandons standard string streams. It utilizes C++17 `std::string_view` and low-level `<charconv>` (`std::from_chars`) to parse CSV datasets directly from memory buffers.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
