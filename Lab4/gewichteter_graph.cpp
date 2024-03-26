#include "gewichteter_graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <climits>
using namespace std;
void GewichteterGraph::minimumspanningtree(int start) {
    // Inițializăm vectorii pentru a ține evidența nodurilor vizitate, a părinților și a distanțelor
    vector<int> visited(adjacency_list.size(), false);
    vector<int> parent(adjacency_list.size(), -1);
    vector<int> distance(adjacency_list.size(), INT_MAX);

    // Cream o coada cu prioritate pentru a stoca nodurile din graf în ordinea distanței lor față de nodul start
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, start)); // Adăugăm nodul start în coada cu prioritate
    distance[start] = 0; // Distanta pana la start este 0

    // Parcurgem coada cu prioritate
    while (!pq.empty()) {
        int v = pq.top().second; // Extragem nodul cu cea mai mica distanta de la start
        pq.pop();
        visited[v] = true; // Marchez nodul ca fiind vizitat

        // Parcurgem toate nodurile adiacente nodului v
        for (int i = 0; i < adjacency_list[v].size(); i++) {
            int u = adjacency_list[v][i]; // Luam un nod adiacent
            int weight = weights[v][u]; // Calculam greutatea muchiei dintre nodurile v si u

            // Daca nodul u nu a fost vizitat si distanta pana la u prin v este mai mica decat distanta curenta
            if (!visited[u] && weight < distance[u]) {
                parent[u] = v; // Setam parintele lui u ca fiind v
                distance[u] = weight; // Setam distanta pana la u ca fiind greutatea muchiei v-u
                pq.push(make_pair(distance[u], u)); // Adaugam u in coada cu prioritate cu noua distanta
            }
        }
    }

    int total_weight = 0;
    cout << "Marginile arborelui de acoperire minim: " << std::endl;

    // Parcurgem vectorul de parinti pentru a afisa muchiile arborelui de acoperire minim
    for (int i = 0; i < parent.size(); i++) {
        if (parent[i] != -1) {
            total_weight += weights[i][parent[i]]; // Calculam greutatea totala a arborelui de acoperire minim
            cout << parent[i] << " - " << i << " (cost: " << weights[i][parent[i]] << ")" << std::endl; // Afisam muchia si greutatea ei
        }
    }
    cout << "Costul total al arborelui de acoperire minim: " << total_weight << endl; // Afisam greutatea totala a arborelui de acoperire minim
}

GewichteterGraph::GewichteterGraph(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Nu s-a deschis fisierul: " << filename << endl;
        return;
    }

    int n, m;
    file >> n >> m;
    for (int i = 0; i < n; i++) { // adaugam noduri la graf
        add_node(i);
    }
    weights.resize(n, vector<int>(n, 0)); // redimensionam matricea de greutate

    for (int i = 0; i < m; i++) { // adaugam muchii in graf
        int v1, v2, weight;
        file >> v1 >> v2 >> weight;
        add_edge(v1, v2); // adaugam muchia (v1, v2)
        add_weighted_edge(v1, v2, weight); // adaugam greutatea muchiei (v1, v2)
        add_edge(v2, v1); // adaugam muchia (v2, v1)
        add_weighted_edge(v2, v1, weight); // adaugam greutatea muchiei (v2, v1)
    }
}


void GewichteterGraph::add_weighted_edge(int v1, int v2, int weight) {
    weights[v1][v2] = weight; // adaugam greutatea muchiei (v1, v2) in matricea de greutate
}
