#include "Graph.h"
using namespace std;

MazeGraph::MazeGraph(int numNodes) : adjacencyList(numNodes) {}

void MazeGraph::addEdge(int fromNode, int toNode) {
    adjacencyList[fromNode].push_back(toNode);
}

// Returns a constant reference to a vector of integers representing the neighbors of the given node in the adjacencyList
const vector<int>& MazeGraph::getNeighbors(int node) const {
    return adjacencyList[node];
}

// Returns the number of nodes in the graph as the size of the adjacencyList vector
int MazeGraph::getNumNodes() const {
    return adjacencyList.size();
}
