#include "Matrix.h"

Matrix::Matrix(int graphSize) {
    //Alokujemy pamięć dla tablicy przechowującej informacje o grafie.
    this->graphSize = graphSize;
    base = new int[graphSize * graphSize];

    //Zerujemy tablicę.
    for (int i = 0; i < graphSize; i++)
        for (int j = 0; j < graphSize; j++)
            base[i * graphSize + j] = INT_MAX;
}

Matrix::~Matrix() {
    delete[] base;
}

void Matrix::addEdge(int startVertex, int endVertex, int weight) {
    base[startVertex * graphSize + endVertex] = weight;
}

int Matrix::findEdge(int startVertex, int endVertex) {
    int value;
    value = base[startVertex * graphSize + endVertex];
    return value;
}

int Matrix::getSize() {
    return graphSize;
}

void Matrix::display() {
    //Obliczamy ilość cyfr potrzebną do zapisania danej liczby.
    int padding = ceil(std::log10(graphSize * graphSize));
    for (int i = 0; i < graphSize; i++) {
        for (int j = 0; j < graphSize; j++) {
            int value = base[i * graphSize + j];
            if (value == INT_MAX)
                value = 0;
            //Wyrównujemy do lewej na podstawie maksymalnej wielkości.
            std::cout << std::setw(padding) << value << ' ';
        }
        std::cout << "\n";
    }
}