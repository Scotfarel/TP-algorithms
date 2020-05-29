//
// Created by ivan on 5/29/20.
//

#include "../headers/ArcGraph.h"

ArcGraph::ArcGraph(size_t vertices_count) {
    verticesCount = vertices_count;
}

ArcGraph::ArcGraph(const IGraph &graph) {
    int newVerticesCount = graph.VerticesCount();
    verticesCount = newVerticesCount;

    for (int i = 0; i < newVerticesCount; i++) {
        std::vector<int> vertices = graph.GetNextVertices(i);
        for (int j: vertices) {
            AddEdge(i, j);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    graphEdges.push_back(std::pair<int, int>(from, to));
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    for (std::pair<int, int> edge: graphEdges) {
        if (edge.first == vertex)
            nextVertices.push_back(edge.second);
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    for (std::pair<int, int> edge: graphEdges) {
        if (edge.second == vertex)
            prevVertices.push_back(edge.first);
    }
    return prevVertices;
}

