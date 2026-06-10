#include "../include/DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>


DataLoader::DataLoader(const std::string& path, int incols, int outcols)
    : filepath(path), inputCols(incols), outputCols(outcols) {}