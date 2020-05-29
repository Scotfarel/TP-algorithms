//
// Created by ivan on 5/29/20.
//

#include "../headers/SetGraph.h"

SetGraph::SetGraph(size_t vertices_count) {
    straightVertices.resize(vertices_count);
    adjectiveVertices.resize(vertices_count);
};

SetGraph::SetGraph(const IGraph &graph) {
    int newVerticesNum = graph.VerticesCount();
    straightVertices.resize(newVerticesNum);
    adjectiveVertices.resize(newVerticesNum);

    for (int i = 0; i < newVerticesNum; i++) {
        std::vector<int> newVertices = graph.GetNextVertices(i);
        for (int j: newVertices) {
            AddEdge(i, j);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjectiveVertices[to].insert(from);
    straightVertices[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return straightVertices.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (int i: straightVertices[vertex])
        nextVertices.push_back(i);
    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (int i: adjectiveVertices[vertex])
        prevVertices.push_back(i);
    return prevVertices;
}

