#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "../GraphsImpl/Matrix.h"
#include "../GraphsImpl/List.h"
#include "../GraphsImpl/Utility.h"
#include "../GraphsImpl/Edge.h"
#include "../GraphsImpl/BinaryHeap.h"


class Prim {
private:
    int *key;

    int *connection;

    BinaryHeap<ListItem> vertexQueue;
public:

    explicit Prim(int size);

    ~Prim();

    void proccessMatrix(Matrix *graph);

    void proccessList(List *graph);

    int *getKeyArray();

    int *getConnectionArray();
};