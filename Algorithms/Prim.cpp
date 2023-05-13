#include <climits>
#include "Prim.h"

Prim::Prim(int size) {
    key = new int[size];
    connection = new int[size];
}

Prim::~Prim() {
    delete[] key;
    delete[] connection;
}

void Prim::proccessMatrix(Matrix *graph) {
    for (int i = 0; i < graph->getSize(); i++)
        key[i] = INT_MAX;

    //Wierzchołek początkowy jest wybierany losowo.
    int startingVertex = rand() % graph->getSize();
    key[startingVertex] = 0;
    connection[startingVertex] = -1;

    //Do kolejki priorytetowej dodajemy wszystkie krawędzie wychodzące z wylosowanego wierzchołka.
    for (int i = 0; i < graph->getSize(); i++)
        vertexQueue.insert({i, key[i]});

    //Dopóki nasze drzewo nie zawiera wszystkich wierzchołków znajdujących się w grafie,
    //dodajemy do niego wierzchołek o najmniejszej wadze przejścia oraz aktualizujemy kolejkę wierzchołków.
    while (!vertexQueue.isEmpty()) {
        auto item = vertexQueue.pop();
        for (int i = 0; i < graph->getSize(); i++) {
            int weight = graph->findEdge(item.vertex, i);
            if (weight != INT_MAX) {
                if (vertexQueue.find({i, key[i]}) && weight < key[i]) {
                    vertexQueue.updateQueue({i, key[i]}, {i, weight});
                    key[i] = weight;
                    connection[i] = item.vertex;
                }
            }
        }
    }
}

void Prim::proccessList(List *graph) {
    for (int i = 0; i < graph->getSize(); i++)
        key[i] = INT_MAX;

    int startingVertex = rand() % graph->getSize();
    key[startingVertex] = 0;
    connection[startingVertex] = -1;

    for (int i = 0; i < graph->getSize(); i++)
        vertexQueue.insert({i, key[i]});

    while (!vertexQueue.isEmpty()) {
        auto item = vertexQueue.pop();
        //Dla reprezentacji listowej mamy dokładnie tyle iteracji, ile krawędzi wychodzi z danego wierzchołka.
        for (auto edge: graph->getListForVertex(item.vertex)) {
            int vertex = edge.vertex;
            if (vertexQueue.find({vertex, key[vertex]}) && edge.weight < key[vertex]) {
                vertexQueue.updateQueue({vertex, key[vertex]}, {vertex, edge.weight});
                key[vertex] = edge.weight;
                connection[vertex] = item.vertex;
            }
        }
    }
}

int *Prim::getKeyArray() {
    return key;
}

int *Prim::getConnectionArray() {
    return connection;
}