#ifndef GEWICHTETER_GRAPH_H
#define GEWICHTETER_GRAPH_H
using namespace std;
#include "Graph.h"
#include <vector>
#include <string>

class GewichteterGraph : public Graph {
public:
    GewichteterGraph(const string& filename);
private:
    void add_weighted_edge(int v1, int v2, int weight);
    vector<vector<int>> weights;
    void minimumspanningtree(int start);

};

#endif
