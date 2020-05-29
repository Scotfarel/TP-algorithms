//
// Created by ivan on 5/28/20.
//

#ifndef INC_311IGRAPH_IGRAPH_H
#define INC_311IGRAPH_IGRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct IGraph {
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //INC_311IGRAPH_IGRAPH_H
