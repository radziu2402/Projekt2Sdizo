#include <iostream>
#include <ctime>
#include "Menu/ShortestPathMenu.h"
#include "Menu/MinimumSpanningMenu.h"

using namespace std;

int main() {
    srand(std::time(nullptr));
    auto *path = new ShortestPathMenu();
    auto *mst = new MinimumSpanningMenu();
    int choise = -1;

    while (choise != 0) {
        cout << "Select data structure:" << endl;
        cout << "   1. Problem najkrótszej ścieżki" << endl;
        cout << "   2. Problem minimalnego drzewa rozpinającego" << endl;
        cout << "   0. Exit" << endl << endl;
        cout << "Choise: ";
        cin >> choise;
        switch (choise) {
            case 0:
                return 0;
            case 1:
                    path->processInput();
                break;
            case 2:
                    mst->processInput();
                break;
            default:
                cout << "Wrong choise!" << endl;
                break;
        }
    }
    return 0;
}