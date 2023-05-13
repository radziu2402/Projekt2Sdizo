#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <climits>
#include "../GraphsImpl/Matrix.h"
#include "../GraphsImpl/List.h"
#include "../GraphsImpl/Utility.h"
#include "../GraphsImpl/BinaryHeap.h"

class Dijkstra {
private:

    BinaryHeap<ListItem> vertexQueue;

    int *distance;

    int *predeccesor;
public:

    explicit Dijkstra(int size);

    ~Dijkstra();

    void proccessMatrix(Matrix *graph, int startingVertex);

    void proccessList(List *graph, int startingVertex);

    int *getDistanceArray();

    int *getPredeccesorArray();
};