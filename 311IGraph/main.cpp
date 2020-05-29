#include <iostream>
#include <cassert>

#include "headers/ListGraph.h"
#include "headers/MatrixGraph.h"
#include "headers/SetGraph.h"
#include "headers/ArcGraph.h"

void test();

int main() {
    test();
    return 0;
}

void test() {
    MatrixGraph matrixGraph(5);
    matrixGraph.AddEdge(0, 1);
    matrixGraph.AddEdge(0, 2);
    matrixGraph.AddEdge(1, 3);
    matrixGraph.AddEdge(2, 3);
    matrixGraph.AddEdge(4, 5);

    ListGraph listGraph(matrixGraph);
    SetGraph setGraph(listGraph);
    ArcGraph arcGraph(setGraph);

    assert(listGraph.GetNextVertices(1) == matrixGraph.GetNextVertices(1));
    assert(setGraph.GetPrevVertices(2) == arcGraph.GetPrevVertices(2));
    assert(listGraph.VerticesCount() == setGraph.VerticesCount());
    assert(arcGraph.VerticesCount() == matrixGraph.VerticesCount());
    assert(listGraph.VerticesCount() == matrixGraph.VerticesCount());

    std::cout << "All tests SUCCESS" << std::endl;
}