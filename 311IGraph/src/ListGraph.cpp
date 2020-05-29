//
// Created by ivan on 5/28/20.
//

#include "../headers/ListGraph.h"


ListGraph::ListGraph(size_t vertices_count) : vertices(vertices_count) {};

ListGraph::ListGraph(const IGraph &graph) {
    int newVerticesNum = graph.VerticesCount();

    vertices.resize(newVerticesNum);
    for (int i = 0; i < newVerticesNum; i++) {
        std::vector<int> newVertices = graph.GetNextVertices(i);
        for (int j: newVertices) {
            AddEdge(i, j);
        }
    }
}

void ListGraph::AddEdge(int from, int to) {
    vertices[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return vertices.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    result.resize(vertices[vertex].size());
    std::copy(vertices[vertex].begin(), vertices[vertex].end(), result.begin());

    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < vertices.size(); ++i) {
        for (int v : vertices[i]) {
            if (v == vertex) {
                result.push_back(i);
            }
        }
    }
    return result;
}


