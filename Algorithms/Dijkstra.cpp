#include "Dijkstra.h"

Dijkstra::Dijkstra(int size) {
    //Alokujemy pamięć dla odpowiednich tablic.
    distance = new int[size];
    predeccesor = new int[size];
}

Dijkstra::~Dijkstra() {
    //Dealokujemy tablice dynamiczne.
    delete[] distance;
    delete[] predeccesor;
}

void Dijkstra::proccessMatrix(Matrix *graph, int startingVertex) {
    for (int i = 0; i < graph->getSize(); i++) {
        //Dla każdego wierzchołka ustawiamy odległość na nieskończoność.
        distance[i] = INT_MAX;
        //Poprzednik jest niezdefiniowany.
        predeccesor[i] = -1;
    }

    //Wierzchołek startowy ma odległość równą zero.
    distance[startingVertex] = 0;
    //Wypełniamy kolejkę priorytetową.
    for (int i = 0; i < graph->getSize(); i++) {
        ListItem item{i, distance[i]};
        vertexQueue.insert(item);
    }

    while (!vertexQueue.isEmpty()) {
        //Dopóki kolejka nie jest pusta, usuwamy wierzchołek o najniższym priorytecie.
        auto item = vertexQueue.pop();
        //Dla każdego sąsiada wykonujemy relaksację krawędzi.
        for (int i = 0; i < graph->getSize(); i++) {
            int weight = graph->findEdge(item.vertex, i);
            if (weight != INT_MAX) {
                if (distance[item.vertex] + weight < distance[i] && distance[item.vertex] != INT_MAX) {
                    ListItem updateItem = {i, distance[i]};
                    distance[i] = distance[item.vertex] + weight;
                    predeccesor[i] = item.vertex;
                    vertexQueue.updateQueue(updateItem, {i, distance[i]});
                }
            }
        }
    }
}

void Dijkstra::proccessList(List *graph, int startingVertex) {
    for (int i = 0; i < graph->getSize(); i++) {
        distance[i] = INT_MAX;
        predeccesor[i] = -1;
    }

    distance[startingVertex] = 0;
    for (int i = 0; i < graph->getSize(); i++) {
        ListItem item{i, distance[i]};
        vertexQueue.insert(item);
    }

    while (!vertexQueue.isEmpty()) {
        auto item = vertexQueue.pop();
        for (int i = 0; i < graph->getSize(); i++) {
            int weight = graph->findEdge(item.vertex, i);
            if (weight != INT_MAX) {
                if (distance[item.vertex] + weight < distance[i] && distance[item.vertex] != INT_MAX) {
                    ListItem updateItem = {i, distance[i]};
                    distance[i] = distance[item.vertex] + weight;
                    predeccesor[i] = item.vertex;
                    vertexQueue.updateQueue(updateItem, {i, distance[i]});
                }
            }
        }
    }
}

int *Dijkstra::getDistanceArray() {
    return distance;
}

int *Dijkstra::getPredeccesorArray() {
    return predeccesor;
}