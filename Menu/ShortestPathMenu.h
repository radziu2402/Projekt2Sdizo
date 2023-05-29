#include <iostream>
#include "../Algorithms/Dijkstra.h"
#include "../Algorithms/FordBellman.h"
#include "../Tests/ShortestPathTest.h"


class ShortestPathMenu {
private:
    Matrix *matrix{};
    List *list{};
    int startingVertex{};
    bool backTyped = false;

    void printMenu();

    void loadFile();

    void createRandom();

    void display();

    void executeFirst();

    void executeSecond();

    void test();

    void displayAlgorithmResult(int *distance, int *predeccesor);

public:

    ShortestPathMenu();

    void processInput();
};
