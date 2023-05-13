#include "FordBellman.h"

FordBellman::FordBellman(int size) {
    //Alokujemy pamięć dla odpowiednich tablic.
    distance = new int[size];
    predeccesor = new int[size];
}

FordBellman::~FordBellman() {
    //Dealokujemy tablice dynamiczne.
    delete[] distance;
    delete[] predeccesor;
}

void FordBellman::proccessMatrix(Matrix *graph, int startingVertex) {
    for (int i = 0; i < graph->getSize(); i++) {
        //Dla każdego wierzchołka ustawiamy odległość na nieskończoność.
        distance[i] = INT_MAX;
        //Poprzednik każdego z wierzchołków jest niezdefiniowany.
        predeccesor[i] = -1;
    }

    //Odległość do wierzchołka startowego jest równa 0.
    distance[startingVertex] = 0;
    for (int i = 0; i < graph->getSize(); i++) {
        //Dla każdej krawędzi (w reprezentacji macierzowej musimy przejść przez wszystkie możliwe),
        //wykonujemy relaksację.
        for (int u = 0; u < graph->getSize(); u++) {
            for (int v = 0; v < graph->getSize(); v++) {
                int weight = graph->findEdge(u, v);
                if (weight != INT_MAX) {
                    if (distance[u] + weight < distance[v] && distance[u] != INT_MAX) {
                        distance[v] = distance[u] + weight;
                        predeccesor[v] = u;
                    }
                }
            }
        }
    }
}

void FordBellman::proccessList(List *graph, int startingVertex) {
    for (int i = 0; i < graph->getSize(); i++) {
        distance[i] = INT_MAX;
        predeccesor[i] = -1;
    }

    distance[startingVertex] = 0;
    for (int i = 0; i < graph->getSize(); i++) {
        for (int u = 0; u < graph->getSize(); u++) {
            //W reprezentacji listowej wystarczy przejście przez odpowiednie listy dla każdego z wierzchołków.
            for (auto item: graph->getListForVertex(u)) {
                if (distance[u] + item.weight < distance[item.vertex] && distance[u] != INT_MAX) {
                    distance[item.vertex] = distance[u] + item.weight;
                    predeccesor[item.vertex] = u;
                }
            }
        }
    }
}

int *FordBellman::getDistanceArray() {
    return distance;
}

int *FordBellman::getPredeccesorArray() {
    return predeccesor;
}