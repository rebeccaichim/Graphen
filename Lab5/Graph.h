#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#define INFINITY std::numeric_limits<int>::max()

class Graph {
private:
    struct Edge {
        int source;
        int destination;
        int weight;
    };

    std::vector<Edge> edges;
    std::vector<int> distances;
    std::vector<int> predecessors;

public:
    Graph(const std::string& filename);
    void addEdge(int source, int destination, int weight);
    void printShortestPath(int startNode, int endNode);
};

#endif // GRAPH_H