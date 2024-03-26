#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph() {}

void Graph::add_node(int node) {
    if (node >= adjacency_list.size()) {
        adjacency_list.resize(node + 1,vector<int>());
    }
}

void Graph::add_edge(int v1, int v2) {
    adjacency_list[v1].push_back(v2);
}

void Graph::print() const {
    cout << "Adjacency List:\n";
    for (int i = 0; i < adjacency_list.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < adjacency_list[i].size(); j++) {
            cout << adjacency_list[i][j] << " ";
        }
        cout << endl;
    }
}
