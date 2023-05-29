#include "MSTTest.h"

MSTTest::MSTTest() {
    matrix = nullptr;
    list = nullptr;
}

MSTTest::~MSTTest() {
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
}

void MSTTest::generateGraph(int vertexCount, int density) {
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
    matrix = new Matrix(vertexCount);
    list = new List(vertexCount);

    //Maksymalna ilość wierzchołków to suma ciągu arytmetycznego an = n.
    int maxEdges = static_cast<int>(density / 100.0f * (((vertexCount + 1) / 2.0f) * vertexCount));
    int edgeCount = 0;
    //Generujemy drzewo rozpinające.
    for (int i = 0; i < vertexCount - 1; i++) {
        //Dla problemu minimalnego drzewa rozpinającego krawędzie są nieskierowane.
        int weight = (rand() % maxEdges) + 1;
        matrix->addEdge(i, i + 1, weight);
        matrix->addEdge(i + 1, i, weight);

        list->addEdge(i, i + 1, weight);
        list->addEdge(i + 1, i, weight);
        edgeCount++;
    }

    //Dodajemy pozostałe krawędzie (zawsze zostanie wygenerowane chociaż drzewo rozpinające).
    while (edgeCount < maxEdges) {
        int start = rand() % vertexCount;
        int end = rand() % vertexCount;
        int weight = (rand() % maxEdges) + 1;

        if (matrix->findEdge(start, end) == INT_MAX) {
            matrix->addEdge(start, end, weight);
            matrix->addEdge(end, start, weight);
            list->addEdge(start, end, weight);
            list->addEdge(end, start, weight);
            edgeCount++;
        }
    }
}

TimeMeasurement MSTTest::primTest(int vertexCount, int density, Prim *prim) {
    TimeMeasurement timeMeasurement{};
    timeMeasurement.first = 0;
    timeMeasurement.second = 0;
    for (int i = 0; i < 100; i++) {
        generateGraph(vertexCount, density);
        measurement.startTimer();
        prim->proccessMatrix(matrix);
        measurement.stopTimer();
        timeMeasurement.first += measurement.getDuration();

        measurement.startTimer();
        prim->proccessList(list);
        measurement.stopTimer();
        timeMeasurement.second += measurement.getDuration();
    }

    timeMeasurement.first /= 100;
    timeMeasurement.second /= 100;
    return timeMeasurement;
}

TimeMeasurement MSTTest::kruskalTest(int vertexCount, int density, Kruskal *kruskal) {
    TimeMeasurement timeMeasurement{};
    timeMeasurement.first = 0;
    timeMeasurement.second = 0;
    for (int i = 0; i < 100; i++) {
        generateGraph(vertexCount, density);
        measurement.startTimer();
        kruskal->proccessMatrix(matrix);
        measurement.stopTimer();
        timeMeasurement.first += measurement.getDuration();

        kruskal->resetContainers();
        measurement.startTimer();
        kruskal->proccessList(list);
        kruskal->resetContainers();
        measurement.stopTimer();
        timeMeasurement.second += measurement.getDuration();
    }

    timeMeasurement.first /= 100;
    timeMeasurement.second /= 100;
    return timeMeasurement;
}

void MSTTest::executionTestAverage() {
    int vertexCounts[] = {10, 25, 50, 75, 100 };
    int densities[] = {25, 50, 75, 99};
    std::ofstream file;
    file.open("mstResult.txt");
    file << "prim" << "\n";
    file << "L - MATRIX   R - LIST" << "\n";
    if (file.is_open()) {
        for (auto count: vertexCounts) {
            file << "vertexcount: " << count << "\n";
            auto *prim = new Prim(count);
            for (auto density: densities) {
                file << "density: " << density << "\n";
                auto time = primTest(count, density, prim);
                file << time.first << " " << time.second << "\n";
            }
            delete prim;
        }

        file << "\n";
        file << "kruskal" << "\n";
        auto *kruskal = new Kruskal();
        for (auto count: vertexCounts) {
            file << "vertexcount: " << count << "\n";
            for (auto density: densities) {
                file << "density: " << density << "\n";
                auto time = kruskalTest(count, density, kruskal);
                file << time.first << " " << time.second << "\n";
            }
        }
        delete kruskal;
    }
    file.close();
}