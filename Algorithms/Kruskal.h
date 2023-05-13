#pragma once

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include "../GraphsImpl/Matrix.h"
#include "../GraphsImpl/List.h"
#include "../GraphsImpl/Utility.h"
#include "../GraphsImpl/Edge.h"

struct Subset {
    int parent;
    int rank;
};

class Kruskal {
private:
    std::list<Edge> edgeList;

    static int find(Subset *subsets, int element);

    static void setUnion(Subset *subsets, int first, int second);

public:
    Kruskal();

    ~Kruskal();

    void proccessMatrix(Matrix *graph);

    void proccessList(List *graph);

    std::list<Edge> &getEdgeList();

    void resetContainers();
};