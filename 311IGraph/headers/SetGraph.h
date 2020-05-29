//
// Created by ivan on 5/29/20.
//

#ifndef INC_311IGRAPH_SETGRAPH_H
#define INC_311IGRAPH_SETGRAPH_H

#include <set>

#include "IGraph.h"

class SetGraph: public IGraph {
public:
    explicit SetGraph(size_t vertices_count);
    SetGraph(const IGraph& graph);
    virtual ~SetGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> straightVertices;
    std::vector<std::set<int>> adjectiveVertices;
};

#endif //INC_311IGRAPH_SETGRAPH_H
