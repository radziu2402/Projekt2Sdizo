#include <iostream>
#include "../Algorithms/Prim.h"
#include "../Algorithms/Kruskal.h"
#include "../Tests/MSTTest.h"

class MinimumSpanningMenu {
private:
    Matrix *matrix{};
    List *list{};
    bool backTyped = false;

    void printMenu();

    void loadFile();

    void createRandom();

    void display();

    void executeFirst();

    void executeSecond();

    void test();

    static void displayKruskalResult(std::list<Edge> &edgeList);

    static void displayPrimResult(int *key, int *connection, int size);

public:

    MinimumSpanningMenu();

    void processInput();
};

