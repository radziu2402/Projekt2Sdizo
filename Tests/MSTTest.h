#include "../Algorithms/Prim.h"
#include "../Algorithms/Kruskal.h"
#include "TimeCounter.h"
#include <fstream>

class MSTTest {
private:
    Matrix *matrix;
    List *list;
    TimeCounter measurement;

    void generateGraph(int vertexCount, int density);

    TimeMeasurement primTest(int vertexCount, int density, Prim *prim);

    TimeMeasurement kruskalTest(int vertexCount, int density, Kruskal *kruskal);

public:
    MSTTest();

    ~MSTTest();

    void executionTestAverage();
};