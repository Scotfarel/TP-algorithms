//
//  Created by ivan on 29/05/20.
//
//  Задача 2. Количество различных путей (3 балла)
//
//  Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
//  Найдите количество различных кратчайших путей между заданными вершинами.
//  Требования: сложность O(V+E).
//  Формат ввода.
//  v: кол-во вершин (макс. 50000), n: кол-во ребер (макс. 200000), n пар реберных вершин, пара вершин u, w для запроса.
//  Формат вывода.
//  Количество кратчайших путей от u к w.
//

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cassert>


class Graph {
public:
    explicit Graph(size_t vertices_count) : vertices(vertices_count), verticesCount(vertices_count) {};

    void AddEdge(int from, int to) {
        vertices[from].push_back(to);
        vertices[to].push_back(from);
    }

    int VerticesCount() const { return verticesCount; }

    std::vector<int> GetNextVertices(int vertex) const {
        std::vector<int> result;
        result.resize(vertices[vertex].size());
        std::copy(vertices[vertex].begin(), vertices[vertex].end(), result.begin());
        return result;
    }

private:
    std::vector<std::vector<int>> vertices;
    int verticesCount;
};

int getShortestPaths(const Graph &graph, int start, int end) {
    if (start == end)
        return 0;

    std::vector<int> vertices(graph.VerticesCount(), 0);
    std::vector<int> parents(graph.VerticesCount(), 0);

    std::queue<int> verticesQueue;
    verticesQueue.push(start);

    vertices[start] = 1;
    while (!verticesQueue.empty()) {
        int current = verticesQueue.front();
        verticesQueue.pop();

        std::vector<int> neighbours = graph.GetNextVertices(current);
        for (const int w: neighbours) {
            if (!vertices[w]) {
                verticesQueue.push(w);
                vertices[w] = vertices[current];
                parents[w] = parents[current] + 1;
            } else if (parents[w] == parents[current] + 1) {
                vertices[w] += vertices[current];
            }
        }
    }
    return vertices[end];
}

void run(std::istream &input, std::ostream &output) {
    int verticesNum = 0;
    int graphEdges = 0;
    input >> verticesNum >> graphEdges;

    Graph graph(verticesNum);
    for (int i = 0; i < graphEdges; i++) {
        int from = 0;
        int to = 0;
        input >> from >> to;
        graph.AddEdge(from, to);
    }

    int start = 0;
    int end = 0;
    input >> start >> end;
    output << getShortestPaths(graph, start, end);
}

void testGetShortestPathAlgorithm() {
    {
        //    1
        //  / | \
        // 0  |  3
        //  \ | /
        //    2

        std::stringstream input;
        std::stringstream output;
        input << "4 5 0 1 0 2 1 2 1 3 2 3 0 3";
        run(input, output);
        assert(output.str() == "2");
    }
    {
        //    1
        //  / | \
        // 0  |  3
        //  \ | /
        //    2

        std::stringstream input;
        std::stringstream output;
        input << "4 5 0 1 0 2 1 2 1 3 2 3 0 1";
        run(input, output);
        assert(output.str() == "1");
    }
    {
        //  0      2
        //   \   / |
        //     1   |
        //   /   \ |
        //  4      3

        std::stringstream input;
        std::stringstream output;
        input << "5 5 0 1 1 2 1 3 1 4 2 3 3 4";
        run(input, output);
        assert(output.str() == "1");
    }
    {
        //  0      2
        //   \   / |
        //     1   |
        //   /   \ |
        //  4      3

        std::stringstream input;
        std::stringstream output;
        input << "5 5 0 1 1 2 1 3 1 4 2 3 2 3";
        run(input, output);
        assert(output.str() == "1");
    }
    {
        //    1   3   5
        //   / \ / \ / \
        //  0   2   4   6       every time in path (0, 6) you have 2 choices, => paths at all = 2 * 2 * 2
        //   \ / \ / \ /
        //    9   8   7

        std::stringstream input;
        std::stringstream output;
        input << "10 12 0 1 0 9 1 2 2 3 2 8 2 9 3 4 4 5 4 7 4 8 5 6 6 7 0 6";
        run(input, output);
        assert(output.str() == "8");
    }
    {
        //    1   3   5
        //   / \ / \ / \
        //  0   2   4   6
        //   \ / \ / \ /
        //    9   8   7

        std::stringstream input;
        std::stringstream output;
        input << "10 12 0 1 0 9 1 2 2 3 2 8 2 9 3 4 4 5 4 7 4 8 5 6 6 7 0 7";
        run(input, output);
        assert(output.str() == "4");
    }

}

int main() {
    //run(std::cin, std::cout);
    testGetShortestPathAlgorithm();
    return 0;
}