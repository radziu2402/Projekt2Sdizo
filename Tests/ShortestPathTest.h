#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/FordBellman.h"
#include "TimeCounter.h"
#include <fstream>

class ShortestPathTest {
private:
    Matrix *matrix;
    List *list;
    TimeCounter measurement;

    void generateGraph(int startingVertex, int vertexCount, int density);

    TimeMeasurement dijkstraTest(int vertexCount, int density, Dijkstra *dijkstra);

    TimeMeasurement fordBellmanTest(int vertexCount, int density, FordBellman *fordBellman);

public:
    ShortestPathTest();

    ~ShortestPathTest();

    void executionTestAverage();
};