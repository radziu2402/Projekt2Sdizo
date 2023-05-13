#include "MinimumSpanningMenu.h"

MinimumSpanningMenu::MinimumSpanningMenu() = default;

void MinimumSpanningMenu::printMenu() {
    //Wypisanie menu dla problemu najkrótszej ścieżki.
    std::cout << std::endl;
    std::cout << "Menu dla problemu minimalnego drzewa rozpinającego" << std::endl;
    std::cout << "1. Wczytaj graf z pliku" << std::endl;
    std::cout << "2. Stwórz losowy graf" << std::endl;
    std::cout << "3. Wyświetl" << std::endl;
    std::cout << "4. Algorytm Prima" << std::endl;
    std::cout << "5. Algorytm Kruskala" << std::endl;
    std::cout << "6. Testuj" << std::endl;
    std::cout << "7. Wróć" << std::endl;
    std::cout << "Wybierz opcję: ";
}

void MinimumSpanningMenu::processInput() {
    //Wchodzimy do pętli obsługi opcji.
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
        else std::cout << "Nieznane polecenie!" << std::endl;
    }
    //Jeśli graf został stworzony, dealokujemy pamięć.
    if (matrix != nullptr && list != nullptr) {
        delete matrix;
        delete list;
    }
}

void MinimumSpanningMenu::loadFile() {
    //Standardowe wczytywanie z pliku.
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
        matrix = new Matrix(vertexCount);
        list = new List(vertexCount);
        std::string str;
        std::getline(file, str);
        for (int i = 0; i < edgeCount; i++) {
            int start, end, weight;
            file >> start >> end >> weight;
            matrix->addEdge(start, end, weight);
            matrix->addEdge(end, start, weight);
            list->addEdge(start, end, weight);
            list->addEdge(end, start, weight);
        }
        display();
    } else std::cout << "Podana nazwa pliku jest nieprawidłowa!" << std::endl;
    file.close();
}

void MinimumSpanningMenu::createRandom() {
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

    int maxEdges = static_cast<int>(density / 100.0f * (((vertexCount - 1) / 2.0f) * vertexCount));
    int edgeCount = 0;
    //Generujemy drzewo rozpinające.
    for (int i = 0; i < vertexCount - 1; i++) {
        //Dla problemu minimalnego drzewa rozpinającego krawędzie są nieskierowane.
        int weight = (rand() % maxEdges) + 1;
        matrix->addEdge(i, i + 1, weight);
        matrix->addEdge(i + 1, i, weight);

        list->addEdge(i, i + 1, weight);
        list->addEdge(i + 1, i, weight);
        edgeCount++;
    }

    //Dodajemy pozostałe krawędzie (zawsze zostanie wygenerowane chociaż drzewo rozpinające).
    while (edgeCount < maxEdges) {
        int start = rand() % vertexCount;
        int end = rand() % vertexCount;
        int weight = (rand() % maxEdges) + 1;

        if (matrix->findEdge(start, end) == INT_MAX) {
            matrix->addEdge(start, end, weight);
            matrix->addEdge(end, start, weight);

            list->addEdge(start, end, weight);
            list->addEdge(end, start, weight);
            edgeCount++;
        }
    }
}

void MinimumSpanningMenu::display() {
    //Wyświetla obie reprezentacje.
    if (matrix != nullptr && list != nullptr) {
        std::cout << "\nMacierz sąsiedztwa:" << std::endl;
        matrix->display();
        std::cout << "\nLista sąsiedztwa:" << std::endl;
        list->display();
    } else std::cout << "\nGraf jest pusty!" << std::endl;
}

void MinimumSpanningMenu::executeFirst() {
    //Wykonuje algorytm Prima dla obu reprezentacji grafu.
    if (matrix == nullptr || list == nullptr) {
        std::cout << "\nGraf jest pusty!" << std::endl;
        return;
    }

    auto *prim = new Prim(matrix->getSize());
    prim->proccessMatrix(matrix);
    std::cout << "\nMacierz sąsiedztwa: " << std::endl;
    displayPrimResult(prim->getKeyArray(), prim->getConnectionArray(), matrix->getSize());

    prim->proccessList(list);
    std::cout << "\nLista sąsiedztwa: " << std::endl;
    displayPrimResult(prim->getKeyArray(), prim->getConnectionArray(), matrix->getSize());
    delete prim;
}

void MinimumSpanningMenu::executeSecond() {
    //Wykonuje algorytm Kruskala dla obu reprezentacji grafu.
    if (matrix == nullptr || list == nullptr) {
        std::cout << "\nGraf jest pusty!" << std::endl;
        return;
    }

    auto *kruskal = new Kruskal();
    kruskal->proccessMatrix(matrix);
    std::cout << "\nMacierz sąsiedztwa: " << std::endl;
    displayKruskalResult(kruskal->getEdgeList());
    kruskal->resetContainers();

    kruskal->proccessList(list);
    std::cout << "\nLista sąsiedztwa: " << std::endl;
    displayKruskalResult(kruskal->getEdgeList());
    kruskal->resetContainers();
    delete kruskal;
}

void MinimumSpanningMenu::test() {
    auto *test = new MSTTest();
    test->executionTestAverage();
    delete test;
}


void MinimumSpanningMenu::displayKruskalResult(std::list<Edge> &edgeList) {
    //Wyświetla wynik działania algorytmu (lista krawędzi należących do MSTTest).
    int mstWeight = 0;
    std::cout << "Krawędzie należące do MSTTest: " << std::endl;
    for (auto item: edgeList) {
        std::cout << item.start << ", " << item.end << ", waga: " << item.weight << std::endl;
        mstWeight += item.weight;
    }
    std::cout << "Waga drzewa wynosi: " << mstWeight << std::endl;
}

void MinimumSpanningMenu::displayPrimResult(int *key, int *connection, int size) {
    //Wyświetla wynik działania algorytmu (tablica wag i połączeń).
    int mstWeight = 0;
    std::cout << "Krawędzie należące do MSTTest: " << std::endl;
    for (int i = 0; i < size; i++) {
        if (connection[i] != -1) {
            std::cout << i << ", " << connection[i] << ", waga: " << key[i] << std::endl;
            mstWeight += key[i];
        }
    }
    std::cout << "Waga drzewa wynosi: " << mstWeight << std::endl;
}