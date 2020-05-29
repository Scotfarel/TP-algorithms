//
// Created by ivan on 5/28/20.
//

#ifndef INC_311IGRAPH_MATRIXGRAPH_H
#define INC_311IGRAPH_MATRIXGRAPH_H

#include "IGraph.h"

class MatrixGraph: public IGraph {
public:
    explicit MatrixGraph(size_t vertices_count);
    MatrixGraph(const IGraph &graph);
    virtual ~MatrixGraph() {}

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> matrix;
    int verticesCount;
};


#endif //INC_311IGRAPH_MATRIXGRAPH_H
