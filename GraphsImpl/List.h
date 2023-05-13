#pragma once

#include <iostream>
#include <climits>
#include <list>


struct ListItem {
    int vertex;
    int weight;

    bool operator==(const ListItem &item) {
        return this->vertex == item.vertex && this->weight == item.weight;
    }

    bool operator<(const ListItem &item) {
        return this->weight < item.weight;
    }

    bool operator<=(const ListItem &item) {
        return this->weight <= item.weight;
    }

    bool operator>(const ListItem &item) {
        return this->weight > item.weight;
    }
};

class List {
private:
    const std::string EXCEPTION_DESC = "Nieprawidłowe dane (przekroczony zakres lub zła waga)!";
    std::list<ListItem> *base;
    int graphSize;

    static std::list<ListItem>::iterator findVertex(std::list<ListItem> &list, int vertex);

public:
    explicit List(int graphSize);

    ~List();

    void addEdge(int startVertex, int endVertex, int weight);

    int findEdge(int startVertex, int endVertex);

    std::list<ListItem> &getListForVertex(int vertex);

    int getSize();

    void display();
};