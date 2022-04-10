#include "mathcalculation.h"

MathCalculation::MathCalculation(int xSize, int ySize, std::function<float (float)> func) : func(func) {
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> rand(0, 1);

    matrix.resize(ySize);
    for (int j = 0; j < ySize; j++) {
        matrix[j].resize(xSize);
        for (int i = 0; i < xSize; i++) {
            matrix[j][i] = rand(gen);
        }
    }
}

void MathCalculation::start() {
    for (int j = 0; j < matrix.size(); j++) {
        for (int i = 0; i < matrix[j].size(); i++) {
            matrix[j][i] = func(matrix[j][i]);
            emit result(j * matrix[j].size() + i + 1);
        }
    }
    emit end();
}
