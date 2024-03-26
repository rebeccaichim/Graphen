#include "Graph.h"

Graph::Graph(const std::string& filename) {
    std::ifstream file(filename);
    int source, destination, weight;
    while (file >> source >> destination >> weight) {
        addEdge(source, destination, weight);
    }
    file.close();
}

void Graph::addEdge(int source, int destination, int weight) {
    Edge edge;
    edge.source = source;
    edge.destination = destination;
    edge.weight = weight;
    edges.push_back(edge);
}

void Graph::printShortestPath(int startNode, int endNode) {
    int numNodes = distances.size();

    // Initialize distances and predecessors
    distances.resize(numNodes + 1, INFINITY);
    predecessors.resize(numNodes + 1, -1);
    distances[startNode] = 0;

    // Run Bellman-Ford algorithm
    for (int i = 1; i < numNodes; i++) {
        for (const Edge& edge : edges) {
            int source = edge.source;
            int destination = edge.destination;
            int weight = edge.weight;
            if (distances[source] != INFINITY && distances[source] + weight < distances[destination]) {
                distances[destination] = distances[source] + weight;
                predecessors[destination] = source;
            }
        }
    }

    // Check for negative cycles
    for (const Edge& edge : edges) {
        int source = edge.source;
        int destination = edge.destination;
        int weight = edge.weight;
        if (distances[source] != INFINITY && distances[source] + weight < distances[destination]) {
            std::cout << "Graful contine cicluri negative!" << std::endl;
            return;
        }
    }

    // Print shortest path and distance
    if (distances[endNode] == INFINITY) {
        std::cout << "Nu exista un drum de la nodul de start la nodul de destinatie!" << std::endl;
    } else {
        std::cout << "Cea mai mica distanta de la " << startNode << " la " << endNode << " este: " << distances[endNode] << std::endl;
        std::cout << "Drumul: ";
        std::vector<int> path;
        int currentNode = endNode;
        while (currentNode != -1) {
            path.push_back(currentNode);
            currentNode = predecessors[currentNode];
        }
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << path[i];
            if (i != 0) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}