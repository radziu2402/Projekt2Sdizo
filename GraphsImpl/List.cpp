#include "List.h"

List::List(int graphSize) {
    this->graphSize = graphSize;
    //Alokujemy pamięć na 'graphSize' list.
    base = new std::list<ListItem>[graphSize];
}

List::~List() {
    //Dealokujemy tablicę bazową.
    delete[] base;
}

void List::addEdge(int startVertex, int endVertex, int weight) {
    try {
        //Tworzymy nowy element grafu o zadanej wadze.
        ListItem item{};
        item.vertex = endVertex;
        item.weight = weight;
        base[startVertex].push_back(item);
    }
    catch (std::out_of_range &) {
        throw std::invalid_argument(EXCEPTION_DESC);
    }
}


int List::findEdge(int startVertex, int endVertex) {
    //Zwracamy przepustowość krawędzi dla danych wierzchołków.
    for (auto item: base[startVertex]) {
        if (item.vertex == endVertex) return item.weight;
    }
    return INT_MAX;
}

std::list<ListItem>::iterator List::findVertex(std::list<ListItem> &list, int vertex) {
    //Iterujemy po liście aż do znalezienia danego wierzchołka.
    for (auto it = list.begin(); it != list.end(); it++)
        if ((*it).vertex == vertex) return it;
    return list.end();
}

std::list<ListItem> &List::getListForVertex(int vertex) {
    //Zwraca listę sąsiadów dla danego wierzchołka.
    return base[vertex];
}

int List::getSize() {
    //Zwraca ilość wierzchołków grafu.
    return graphSize;
}

void List::display() {
    //Wyświetla ciąg znaków reprezentujący graf w postaci listy sąsiedztwa.
    for (int i = 0; i < graphSize; i++) {
        std::cout << i << ": ";
        for (auto item: base[i]) std::cout << item.vertex << "(" << item.weight << "), ";
        std::cout << "\b\b" << "  " << "\n";
    }
}