#ifndef MAZE_GRAPH_H
#define MAZE_GRAPH_H

#include <vector>
using namespace std;

class MazeGraph {
public:
    MazeGraph(int numNodes);
    void addEdge(int fromNode, int toNode);
    const vector<int>& getNeighbors(int node) const;
    int getNumNodes() const;

private:
    vector<vector<int>> adjacencyList;
};

#endif