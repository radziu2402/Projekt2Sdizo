cmake_minimum_required(VERSION 3.13)
project(Projekt2)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(Projekt2 Tests/TimeCounter.h Tests/TimeCounter.cpp main.cpp Algorithms/Dijkstra.h Algorithms/Dijkstra.cpp GraphsImpl/Matrix.h GraphsImpl/List.h GraphsImpl/Matrix.cpp GraphsImpl/List.cpp Algorithms/FordBellman.cpp Algorithms/FordBellman.h Menu/ShortestPathMenu.h Menu/MinimumSpanningMenu.h Menu/ShortestPathMenu.cpp Menu/MinimumSpanningMenu.cpp Algorithms/Prim.h Algorithms/Prim.cpp GraphsImpl/Utility.h Algorithms/Kruskal.h Algorithms/Kruskal.cpp GraphsImpl/Edge.h Tests/MSTTest.h Tests/MSTTest.cpp Tests/ShortestPathTest.cpp Tests/ShortestPathTest.h GraphsImpl/BinaryHeap.h)