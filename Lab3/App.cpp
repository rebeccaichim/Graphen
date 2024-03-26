#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include "Graph.h"
#include<iostream>
using namespace std;

void solution() {
    int numRows, numCols;
    std::ifstream inFile("C:\\Users\\User\\Lab3Graphen\\labirint1.txt");

    if (!inFile) {
        cout << "Error opening file." << std::endl;
        return;
    }

    inFile >> numRows >> numCols;
    inFile.ignore();

    MazeGraph maze(numRows * numCols);
    vector<char> grid(numRows * numCols);
    int startNode, endNode;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            char c;
            inFile.get(c);
            int node = i * numCols + j;
            grid[node] = c;

            if (c != 'X') {
                if (c == 'S') {
                    startNode = node;
                } else if (c == 'F') {
                    endNode = node;
                }

                if (i > 0 && grid[node - numCols] != 'X') {
                    maze.addEdge(node, node - numCols);
                    maze.addEdge(node - numCols, node);
                }

                if (j > 0 && grid[node - 1] != 'X') {
                    maze.addEdge(node, node - 1);
                    maze.addEdge(node - 1, node);
                }
            }
        }
        inFile.ignore();
    }

    inFile.close();

    std::queue<int> q;
    std::unordered_set<int> visited;
    std::vector<int> distance(numRows * numCols, -1);
    std::vector<int> previous(numRows * numCols, -1);

    q.push(startNode);
    visited.insert(startNode);
    distance[startNode] = 0;

    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        if (currNode == endNode) {
            // Print the shortest path by backtracking through the previous nodes
            std::vector<int> shortestPath;
            while (currNode != startNode) {
                shortestPath.push_back(currNode);
                currNode = previous[currNode];
            }
            shortestPath.push_back(startNode);

            // Output the shortest path in reverse order
            cout << "Shortest path: ";
            for (auto it = shortestPath.rbegin(); it != shortestPath.rend(); ++it) {
                std::cout << "(" << *it / numCols << "," << *it % numCols << ")";
                if (it != shortestPath.rend() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;
            return;
        }

        for (int neighbor: maze.getNeighbors(currNode)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                distance[neighbor] = distance[currNode] + 1;
                previous[neighbor] = currNode;
            }
        }
    }


    cout << "No path to end found." << std::endl;
}

int main() {
    int numRows, numCols;
    std::ifstream inFile("C:\\Users\\User\\Lab3Graphen\\labirint1.txt");
    // Check if the file is opened successfully
    if (!inFile) {
        cout << "Error opening file." << std::endl;
        return 1;
    }

// Read the number of rows and columns from the input file and ignores newline character
    inFile >> numRows >> numCols;
    inFile.ignore();

// Create the maze graph and grid of characters
    MazeGraph maze(numRows * numCols);
    vector<char> grid(numRows * numCols);
    int startNode, endNode;

// Loop through the input file and create the graph and grid
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            char c;
            inFile.get(c);
            int node = i * numCols + j;
            grid[node] = c;

            // If the character is not an obstacle, create an edge in the maze graph
            if (c != 'X') {
                if (c == 'S') {
                    startNode = node;
                } else if (c == 'F') {
                    endNode = node;
                }

                if (i > 0 && grid[node - numCols] != 'X') {
                    maze.addEdge(node, node - numCols);
                    maze.addEdge(node - numCols, node);
                }

                if (j > 0 && grid[node - 1] != 'X') {
                    maze.addEdge(node, node - 1);
                    maze.addEdge(node - 1, node);
                }
            }
        }
        inFile.ignore();
    }

    inFile.close();



// Initialize variables for breadth-first search
    std::queue<int> q;
    std::unordered_set<int> visited;
    std::vector<int> distance(numRows * numCols, -1);

// Start breadth-first search from the starting node
    q.push(startNode);
    visited.insert(startNode);
    distance[startNode] = 0;

// Continue breadth-first search until the end node is found or all nodes have been visited
    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        // If the end node is found, print the shortest path length and exit the loop
        if (currNode == endNode) {
            cout << "Shortest path length: " << distance[currNode] << std::endl;
            break;
        }

        // Otherwise, add unvisited neighbors to the queue and update the distances
        for (int neighbor: maze.getNeighbors(currNode)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                distance[neighbor] = distance[currNode] + 1;
            }
        }
    }

    return 0;
}