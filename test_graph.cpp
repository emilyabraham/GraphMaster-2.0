#define TEST
#include <iostream>
#include "graph.h"
using namespace std;

int testAddVertex() {
    Graph g;
    vector<int> vertices = {10, 100, 1000, 10000, 100000};
    
    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }
    for (int i = 0; i < vertices.size(); i++) {
        if (!g.contains_vertex(vertices[i])) {
            return 0;
        }
    }
    if (g.numVertices() != vertices.size()) {
        return 0;
    }
    return 5;
}

int testAddEdge() {
    Graph g;
    vector<int> vertices = {5, 10, 15, 20, 25};
    vector<tuple<int, int, int>> edges = {{5, 10, 2}, {10, 20, 12}, {25, 5, 15}, {15, 20, 8}};
    
    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.addEdge(u, v, w);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        if (!g.contains_edge(u, v)) {
            return 0;
        }
        if (!g.contains_edge(v, u)) {
            return 0;
        }
    }

    return 5;
}

int testRemoveEdge() {
    if (testAddEdge() == 0) {
        cout << "You have not passed Add Edge Yet!" << endl;
        return 0;
    }

    Graph g;
    vector<int> vertices = {5, 10, 15, 20, 25};
    vector<tuple<int, int, int>> edges = {{5, 10, 2}, {10, 20, 12}, {25, 5, 15}, {15, 20, 8}};
    
    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.addEdge(u, v, w);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.removeEdge(v, u);

        if (g.contains_edge(u, v) || g.contains_edge(v, u)) {
            return 0;
        }
    } 

    return 10;
}

int testRemoveVertex() {
    if (testAddVertex() == 0 || testRemoveEdge() == 0) {
        cout << "You have not passed add vertex, add edge, or remove edge yet!" << endl;
        return 0;
    }

    Graph g;
    vector<int> vertices = {5, 10, 15, 20, 25};
    vector<tuple<int, int, int>> edges = {{5, 10, 2}, {10, 20, 12}, {25, 5, 15}, {15, 20, 8}};
    
    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.addEdge(u, v, w);
    }

    g.removeVertex(20);
    if (g.contains_edge(10, 20) || g.contains_edge(20, 10)) {
        cout << "Failed" << endl;
        return 0;
    }
    if (g.contains_edge(15, 20) || g.contains_edge(20, 15)) {
        cout << "Failed" << endl;
        return 0;
    }

    cout << "Passed Remove Vertex" << endl;

    return 10;
}

int sumWeights(Graph& g) {
    vector<pair<int, int>> mst = g.primMST();
    int totalWeight = 0;
    for (int i = 0; i < mst.size(); i++) {
        totalWeight += g.getEdgeWeight(mst[i].first, mst[i].second);
    }
    return totalWeight;
}

int testPrims() {
    Graph g;
    vector<int> vertices = {0, 1, 2, 3, 4, 5};
    vector<tuple<int, int, int>> edges = {{0, 1, 12}, {0, 2, 8},
                                          {1, 2, 9}, {1, 3, 22}, {1, 5, 11},
                                          {2, 5, 14}, {2, 3, 16},
                                          {3, 5, 18}, {3, 4, 15},
                                          {4, 5, 3}};

    for (int i = 0; i < vertices.size(); i++) {
        g.addVertex(vertices[i]);
    }

    for (int i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int w = get<2>(edges[i]);
        g.addEdge(v, u, w);
    }
   
    if (sumWeights(g) != 46) {
        cout << "Total cost of minimum spanning tree failed" << endl;
        return 0;
    }

    g.removeEdge(2, 0);
    g.addEdge(0, 2, 4);

    if (sumWeights(g) != 42) {
        cout << "Total cost of minimum spanning tree failed" << endl;
        return 0;
    }

    cout << "Passed Prims" << endl;
    return 50;
}

int main(){
    int score = 0;
    try {
        cout << "Test Add Vertex:" << endl;
        int temp_score = 0;
        temp_score = testAddVertex();
        score += temp_score;
        if (temp_score == 0) {
            cout << "Failed" << endl;
        } else {
            cout << "Passed Add Vertex" << endl;
        }
        cout << endl;

        cout << "Test Add Edge:" << endl;
        temp_score = testAddEdge();
        if (temp_score == 0) {
            cout << "Failed" << endl;
        }
        else {
            cout << "Passed Add Edge" << endl;
        }
        score += temp_score;
        cout << endl;

        cout << "Test Remove Edge:" << endl;
        temp_score = testRemoveEdge();
        if (temp_score == 0) {
            cout << "Failed" << endl;
        }
        else {
            cout << "Passed Remove Edge" << endl;
        }
        score += temp_score;
        cout << endl;

        cout << "Test Remove Vertex:" << endl;
        score += testRemoveVertex();
        cout << endl;

        cout << "Test Prim's Algorithm:" << endl;
        score += testPrims();
        cout << endl;
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }
    
    cout << "Final score: " << score << " / 80" << endl;
    return 0;
}