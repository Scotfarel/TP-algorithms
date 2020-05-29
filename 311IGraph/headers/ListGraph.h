//
// Created by ivan on 5/28/20.
//

#ifndef INC_311IGRAPH_LISTGRAPH_H
#define INC_311IGRAPH_LISTGRAPH_H

#include "IGraph.h"

class ListGraph: public IGraph {
public:
    explicit ListGraph(size_t vertices_count);
    ListGraph(const IGraph& graph);
    virtual ~ListGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> vertices;
};

#endif //INC_311IGRAPH_LISTGRAPH_H
