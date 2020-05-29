//
// Created by ivan on 5/29/20.
//

#ifndef INC_311IGRAPH_ARCGRAPH_H
#define INC_311IGRAPH_ARCGRAPH_H

#include "IGraph.h"

class ArcGraph: public IGraph {
public:
    explicit ArcGraph(size_t vertices_count);
    ArcGraph(const IGraph& graph);
    virtual ~ArcGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> graphEdges;
    int verticesCount;
};

#endif //INC_311IGRAPH_ARCGRAPH_H
