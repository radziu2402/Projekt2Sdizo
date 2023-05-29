#include <set>
#include "ShortestPathMenu.h"

ShortestPathMenu::ShortestPathMenu() = default;

void ShortestPathMenu::printMenu() {
    std::cout << std::endl;
    std::cout << "Menu dla problemu najkrótszej ścieżki" << std::endl;
    std::cout << "1. Wczytaj graf z pliku" << std::endl;
    std::cout << "2. Stwórz losowy graf" << std::endl;
    std::cout << "3. Wyświetl" << std::endl;
    std::cout << "4. Algorytm Dijkstry" << std::endl;
    std::cout << "5. Algorytm Forda-Bellmana" << std::endl;
    std::cout << "6. Testuj" << std::endl;
    std::cout << "7. Wróć" << std::endl;
    std::cout << "Wybierz opcję: ";
}

void ShortestPathMenu::processInput() {
    std::string readConsole;
    backTyped = false;
    while (!backTyped) {
        printMenu();
        std::cin >> readConsole;
        if (readConsole == "1")
            loadFile();
        else if (readConsole == "2")
            createRandom();
        else if (readConsole == "3")
            display();
        else if (readConsole == "4")
            executeFirst();
        else if (readConsole == "5")
            executeSecond();
        else if (readConsole == "6")
            test();
        else if (readConsole == "7")
            backTyped = true;
        else
            std::cout << "Nieznane polecenie!" << std::endl;
    }
    //Jeśli graf został stworzony, dealokujemy pamięć.
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
}

void ShortestPathMenu::loadFile() {
    std::string filename;
    int edgeCount, vertexCount;
    std::cout << "\nPodaj nazwę pliku: ";
    std::cin >> filename;
    std::ifstream file;
    file.open(filename);

    if (file.is_open()) {
        if (matrix != nullptr && list != nullptr) {
            delete matrix;
            delete list;
        }

        file >> edgeCount;
        file >> vertexCount;
        file >> startingVertex;
        matrix = new Matrix(vertexCount);
        list = new List(vertexCount);
        std::string str;
        std::getline(file, str);

        std::set<std::pair<int, int>> edgesSet;  // Zbiór, aby śledzić duplikaty krawędzi
        bool duplicateDetected = false;  // Flaga, która oznacza, czy wykryto duplikat krawędzi

        for (int i = 0; i < edgeCount; i++) {
            int start, end, weight;
            file >> start >> end >> weight;

            // Sprawdź, czy krawędź jest duplikatem
            if (edgesSet.count({start, end}) > 0) {
                duplicateDetected = true;
                break;
            }

            edgesSet.insert({start, end});

            matrix->addEdge(start, end, weight);
            list->addEdge(start, end, weight);
        }

        if (duplicateDetected || edgesSet.size() != edgeCount) {
            std::cout
                    << "Sprawdź plik źródłowy. Wprowadzono niepoprawną ilość krawędzi lub duplikaty. Wczytywanie zostaje przerwane."
                    << std::endl;
            delete matrix;
            delete list;
            matrix = nullptr;
            list = nullptr;
            file.close();
            return;
        }

        display();
    } else {
        std::cout << "Podana nazwa pliku jest nieprawidłowa!" << std::endl;
    }

    file.close();
}

void ShortestPathMenu::createRandom() {
    //Wczytujemy parametry generowanego grafu od użytkownika.
    int vertexCount, density;
    std::cout << "\nPodaj liczbę wierzchołków grafu: ";
    std::cin >> vertexCount;
    std::cout << "Podaj gęstość grafu (w %): ";
    std::cin >> density;

    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
    matrix = new Matrix(vertexCount);
    list = new List(vertexCount);

    startingVertex = rand() % vertexCount;
    int maxEdges = static_cast<int>(density / 100.0f * (vertexCount * vertexCount));
    int edgeCount = 0;
    //Generujemy drzewo rozpinające.
    for (int i = 0; i < vertexCount; i++) {
        if (i == startingVertex)
            continue;
        int weight = (rand() % vertexCount) + 1;
        matrix->addEdge(startingVertex, i, weight);
        list->addEdge(startingVertex, i, weight);
        edgeCount++;
    }

    //Dodajemy pozostałe krawędzie (zawsze zostanie wygenerowane chociaż drzewo rozpinające).
    while (edgeCount < maxEdges) {
        int start = rand() % vertexCount;
        int end = rand() % vertexCount;
        int weight = (rand() % vertexCount) + 1;

        if (matrix->findEdge(start, end) == INT_MAX) {
            matrix->addEdge(start, end, weight);
            list->addEdge(start, end, weight);
            edgeCount++;
        }
    }
}

void ShortestPathMenu::display() {
    //Wyświetla obie reprezentacje.
    if (matrix != nullptr && list != nullptr) {
        std::cout << "\nMacierz sąsiedztwa:" << std::endl;
        matrix->display();
        std::cout << "\nLista sąsiedztwa:" << std::endl;
        list->display();
    } else std::cout << "\nGraf jest pusty!" << std::endl;
}

void ShortestPathMenu::executeFirst() {
    // Sprawdzenie czy istnieją ujemne wagi w grafie
    bool negativeWeightsExist = false;

    if (matrix != nullptr) {
        for (int i = 0; i < matrix->getSize(); i++) {
            for (int j = 0; j < matrix->getSize(); j++) {
                int weight = matrix->findEdge(i, j);
                if (weight < 0) {
                    negativeWeightsExist = true;
                    break;
                }
            }
            if (negativeWeightsExist) {
                break;
            }
        }
    }

    if (negativeWeightsExist) {
        std::cout << "\nGraf zawiera ujemne wagi. Algorytm Dijkstry nie może być zastosowany." << std::endl;
        return;
    }
    //Wykonuje algorytm Dijkstry dla obu reprezentacji grafu.
    if (matrix == nullptr || list == nullptr) {
        std::cout << "\nGraf jest pusty!" << std::endl;
        return;
    }

    auto *dijkstra = new Dijkstra(matrix->getSize());
    dijkstra->proccessMatrix(matrix, startingVertex);
    std::cout << "\nMacierz sąsiedztwa: " << std::endl;
    displayAlgorithmResult(dijkstra->getDistanceArray(), dijkstra->getPredeccesorArray());
    std::cout << std::endl;

    dijkstra->proccessList(list, startingVertex);
    std::cout << "Lista sąsiedztwa: " << std::endl;
    displayAlgorithmResult(dijkstra->getDistanceArray(), dijkstra->getPredeccesorArray());
    delete dijkstra;
}

void ShortestPathMenu::executeSecond() {
    if (matrix == nullptr || list == nullptr) {
        std::cout << "\nGraf jest pusty!" << std::endl;
        return;
    }

    auto* fordBellman = new FordBellman(matrix->getSize());
    fordBellman->proccessMatrix(matrix, startingVertex);
    std::cout << "\nMacierz sąsiedztwa: " << std::endl;
    displayAlgorithmResult(fordBellman->getDistanceArray(), fordBellman->getPredeccesorArray());
    std::cout << std::endl;

    fordBellman->proccessList(list, startingVertex);
    std::cout << "Lista sąsiedztwa: " << std::endl;
    displayAlgorithmResult(fordBellman->getDistanceArray(), fordBellman->getPredeccesorArray());

    if (fordBellman->checkNegativeCycle(matrix)) {
        std::cout << "\nWykryto cykl ujemny w grafie. Wyniki nie będą poprawne." << std::endl;
    } else {
        std::cout << "\nNie wykryto cyklu ujemnego w grafie." << std::endl;
    }
    delete fordBellman;
}

void ShortestPathMenu::test() {
    auto *test = new ShortestPathTest();
    test->executionTestAverage();
    delete test;
}

void ShortestPathMenu::displayAlgorithmResult(int *distance, int *predeccesor) {
    //Wyświetla wynik działania algorytmu (w obu przypadkach tablice odległości i poprzedników).
    std::string representation;
    std::string vertex;

    for (int i = 0; i < matrix->getSize(); i++) {
        if (distance[i] == INT_MAX) continue;
        int currentVertex = i;
        while (currentVertex != startingVertex) {
            vertex.insert(0, std::to_string(predeccesor[currentVertex]) + " -> ");
            currentVertex = predeccesor[currentVertex];
        }

        vertex.append(std::to_string(i));
        representation.append(std::to_string(i) + " (koszt = " + std::to_string(distance[i]) + "): ");
        representation.append(vertex + "\n");
        vertex = "";
    }
    std::cout << representation;
}