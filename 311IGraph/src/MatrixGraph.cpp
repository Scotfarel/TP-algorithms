//
// Created by ivan on 5/28/20.
//

#include "../headers/MatrixGraph.h"

MatrixGraph::MatrixGraph(size_t vertices_count) {
    verticesCount = vertices_count;
    matrix.resize(verticesCount);
    for (auto& edge: matrix) {
        edge.resize(vertices_count, false);
    }
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    int newVerticesCount = graph.VerticesCount();

    for (int i = 0; i < newVerticesCount; i++) {
        matrix[i].resize(newVerticesCount);
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int j: vertices) {
            AddEdge(i, j);
        }
    }

}

void MatrixGraph::AddEdge(int from, int to) {
    matrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (int i = 0; i < verticesCount; i++) {
        if (matrix[vertex][i])
            nextVertices.push_back(i);
    }

    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i = 0; i < verticesCount; i++) {
        if (matrix[i][vertex])
            prevVertices.push_back(i);
    }

    return prevVertices;
}

