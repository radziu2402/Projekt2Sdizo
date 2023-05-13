#pragma once

#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include <string>

class Matrix {
private:
    const std::string EXCEPTION_DESC = "Nieprawidłowe dane (przekroczony zakres lub zła waga)!";
    int *base;

    int graphSize;
public:

    explicit Matrix(int graphSize);

    ~Matrix();

    void addEdge(int startVertex, int endVertex, int weight);

    int findEdge(int startVertex, int endVertex);

    int getSize();

    void display();
};