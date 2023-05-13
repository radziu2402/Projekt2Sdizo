#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include "Edge.h"

class Utility {
public:
    static bool containsEdge(std::vector<Edge> &edgeVector, Edge &edge) {
        return std::find(edgeVector.begin(), edgeVector.end(), edge) != edgeVector.end();
    }
};