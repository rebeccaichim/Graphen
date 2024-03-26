#ifndef GRAPH_H
#define GRAPH_H
using namespace std;
#include <vector>

class Graph {
public:
    Graph();
    void add_node(int node);
    void add_edge(int v1, int v2);
    void print() const;
protected:
    vector<vector<int>> adjacency_list;
};

#endif
