#include "Kruskal.h"

Kruskal::Kruskal() = default;

Kruskal::~Kruskal() = default;

int Kruskal::find(Subset *subsets, int element) {
    //Metoda kompresji ścieżek - zwraca reprezentanta danej grupy.
    if (subsets[element].parent != element)
        subsets[element].parent = find(subsets, subsets[element].parent);
    return subsets[element].parent;
}

void Kruskal::setUnion(Subset *subsets, int first, int second) {
    //Znajdujemy reprezentanta dla obu elementów.
    int firstRoot = find(subsets, first);
    int secondRoot = find(subsets, second);

    //Jeśli rangi są różne, przy łączeniu pozostają takie same.
    if (subsets[firstRoot].rank < subsets[secondRoot].rank)
        subsets[firstRoot].parent = secondRoot;
    else if (subsets[firstRoot].rank > subsets[secondRoot].rank)
        subsets[secondRoot].parent = firstRoot;
    else {
        //Łączenie elementów o tej samej randze zwiększa wysokość drzewa.
        subsets[secondRoot].parent = firstRoot;
        subsets[firstRoot].rank++;
    }
}

void Kruskal::proccessMatrix(Matrix *graph) {
    //Wektor przechowujący krawędzie grafu.
    std::vector<Edge> edgeVector;
    //Zmienna pomocnicza (wystarczy przejść po krawędziach należących do przekątnej głównej
    //oraz znajdujących się pod nią, ponieważ macierz jest symetryczna).
    int diagonal = 1;
    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < diagonal; j++) {
            int weight = graph->findEdge(i, j);
            if (weight != INT_MAX) {
                Edge item = {i, j, weight};
                edgeVector.push_back(item);
            }
        }
        diagonal++;
    }

    //Sortujemy krawędzie rosnąco względem wagi.
    std::sort(edgeVector.begin(), edgeVector.end());
    //Alokujemy pamięć dla podzbiorów.
    auto *subsets = new Subset[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) {
        //Dla każdego podzbioru (początkowo każdy wierzchołek)
        //ustawiamy reprezentanta jako jego samego oraz rangę równą 0.
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int edgeIndex = 0;
    while (edgeList.size() < graph->getSize() - 1) {
        //Pobieramy krawędź o najmniejszej wadze.
        Edge currentEdge = edgeVector[edgeIndex];
        edgeIndex++;

        //Znajdujemy reprezentantów grup do których należą wierzchołek początkowy i końcowy.
        int startSet = find(subsets, currentEdge.start);
        int endSet = find(subsets, currentEdge.end);
        //Jeśli wierzchołki są w innych podzbiorach, łączymy je, a krawędź dodajemy do listy krawędzi MSTTest.
        if (startSet != endSet) {
            edgeList.push_back(currentEdge);
            setUnion(subsets, startSet, endSet);
        }
    }
    delete[] subsets;
}

void Kruskal::proccessList(List *graph) {
    std::vector<Edge> edgeVector;
    for (int i = 0; i < graph->getSize(); i++) {
        //Dla listy sąsiedztwa, przechodzimy po każdym z wierzchołków
        //i sprawdzamy czy taka krawędź nie została już dodana.
        std::list<ListItem> &row = graph->getListForVertex(i);
        for (auto edge: row) {
            Edge item = {i, edge.vertex, edge.weight};
            if (!Utility::containsEdge(edgeVector, item)) edgeVector.push_back(item);
        }
    }

    std::sort(edgeVector.begin(), edgeVector.end());
    auto *subsets = new Subset[graph->getSize()];
    for (int i = 0; i < graph->getSize(); i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int edgeIndex = 0;
    while (edgeList.size() < graph->getSize() - 1) {
        Edge currentEdge = edgeVector[edgeIndex];
        edgeIndex++;

        int startSet = find(subsets, currentEdge.start);
        int endSet = find(subsets, currentEdge.end);
        if (startSet != endSet) {
            edgeList.push_back(currentEdge);
            setUnion(subsets, startSet, endSet);
        }
    }
    delete[] subsets;
}

std::list<Edge> &Kruskal::getEdgeList() {
    return edgeList;
}

void Kruskal::resetContainers() {
    //Czyścimy wynik działania algorytmu.
    edgeList.clear();
}