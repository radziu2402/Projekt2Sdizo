#include "ShortestPathTest.h"

ShortestPathTest::ShortestPathTest() {
    matrix = nullptr;
    list = nullptr;
}

ShortestPathTest::~ShortestPathTest() {
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
}

void ShortestPathTest::generateGraph(int startingVertex, int vertexCount, int density) {
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
    matrix = new Matrix(vertexCount);
    list = new List(vertexCount);

    int maxEdges = static_cast<int>(density / 100.0f * (vertexCount * vertexCount));
    int edgeCount = 0;
    //Generujemy drzewo rozpinające.
    for (int i = 0; i < vertexCount; i++) {
        if (i == startingVertex) continue;
        int weight = (rand() % maxEdges) + 1;
        matrix->addEdge(startingVertex, i, weight);
        list->addEdge(startingVertex, i, weight);
        edgeCount++;
    }

    //Dodajemy pozostałe krawędzie (zawsze zostanie wygenerowane chociaż drzewo rozpinające).
    while (edgeCount < maxEdges) {
        int start = rand() % vertexCount;
        int end = rand() % vertexCount;
        int weight = (rand() % maxEdges) + 1;

        if (matrix->findEdge(start, end) == INT_MAX) {
            matrix->addEdge(start, end, weight);
            list->addEdge(start, end, weight);
            edgeCount++;
        }
    }
}

TimeMeasurement ShortestPathTest::dijkstraTest(int vertexCount, int density, Dijkstra *dijkstra) {
    TimeMeasurement timeMeasurement{};
    timeMeasurement.first = 0;
    timeMeasurement.second = 0;
    for (int i = 0; i < 100; i++) {
        int startingVertex = rand() % vertexCount;
        generateGraph(startingVertex, vertexCount, density);
        measurement.startTimer();
        dijkstra->proccessMatrix(matrix, startingVertex);
        measurement.stopTimer();
        timeMeasurement.first += measurement.getDuration();

        measurement.startTimer();
        dijkstra->proccessList(list, startingVertex);
        measurement.stopTimer();
        timeMeasurement.second += measurement.getDuration();
    }
    timeMeasurement.first /= 100;
    timeMeasurement.second /= 100;
    return timeMeasurement;
}

TimeMeasurement ShortestPathTest::fordBellmanTest(int vertexCount, int density, FordBellman *fordBellman) {
    TimeMeasurement timeMeasurement{};
    timeMeasurement.first = 0;
    timeMeasurement.second = 0;
    for (int i = 0; i < 100; i++) {
        int startingVertex = rand() % vertexCount;
        generateGraph(startingVertex, vertexCount, density);
        measurement.startTimer();
        fordBellman->proccessMatrix(matrix, startingVertex);
        measurement.stopTimer();
        timeMeasurement.first += measurement.getDuration();

        measurement.startTimer();
        fordBellman->proccessList(list, startingVertex);
        measurement.stopTimer();
        timeMeasurement.second += measurement.getDuration();
    }
    timeMeasurement.first /= 100;
    timeMeasurement.second /= 100;
    return timeMeasurement;
}

void ShortestPathTest::executionTestAverage() {
    int vertexCounts[] = {10, 25, 50, 75, 100 };
    int densities[] = {20, 50, 75, 99};
    std::ofstream file;
    file.open("sptResult.txt");
    if (file.is_open()) {
        file << "dijkstra" << "\n";
        file << "L - MATRIX   R - LIST" << "\n";
        for (auto count: vertexCounts) {
            auto *dijkstra = new Dijkstra(count);
            file << "vertexcount: " << count << "\n";
            for (auto density: densities) {
                file << "density: " << density << "\n";
                auto time = dijkstraTest(count, density, dijkstra);
                file << time.first << " " << time.second << "\n";
            }
            delete dijkstra;
        }

        file << "\n";
        file << "fordBellman" << "\n";
        for (auto count: vertexCounts) {
            auto *fordBellman = new FordBellman(count);
            file << "vertexcount: " << count << "\n";
            for (auto density: densities) {
                file << "density: " << density << "\n";
                auto time = fordBellmanTest(count, density, fordBellman);
                file << time.first << " " << time.second << "\n";
            }
            delete fordBellman;
        }
    }
    file.close();
}