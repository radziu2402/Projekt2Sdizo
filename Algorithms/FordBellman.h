#pragma once

#include <string>
#include <climits>
#include "../GraphsImpl/Matrix.h"
#include "../GraphsImpl/List.h"

class FordBellman {
private:

    int *distance;

    int *predeccesor;
public:

    explicit FordBellman(int size);

    ~FordBellman();

    void proccessMatrix(Matrix *graph, int startingVertex);

    void proccessList(List *graph, int startingVertex);

    int *getDistanceArray();

    int *getPredeccesorArray();

    bool checkNegativeCycle(Matrix *graph);
};
