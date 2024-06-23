#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Graph {
    private:
        unordered_map<int, unordered_map<int, int>> adjList;

    public:
        Graph() {};

        bool contains_vertex(int u) {
            return adjList.find(u) != adjList.end();
        }

        bool contains_edge(int u, int v) {
            return adjList[u].find(v) != adjList[u].end();
        }

        void addVertex(int u) {
            if (!contains_vertex(u))
                adjList[u] = unordered_map<int, int>();
         
        }

        void addEdge(int u, int v, int w) {
            addVertex(u);
            addVertex(v);
            adjList[u][v] = w;
            adjList[v][u] = w;
        
        }

        void removeEdge(int u, int v) {
            if (contains_edge(u, v)) {
            adjList[u].erase(v);
            adjList[v].erase(u);
        }
            
        }

        void removeVertex(int id) {
            if (contains_vertex(id)) {
                for (auto& [u, neighbors] : adjList) {
                    neighbors.erase(id);
                }
                adjList.erase(id);
        }
            
        }

        int numVertices() {
            return adjList.size();
        }

        int getEdgeWeight(int u, int v) {
            if (contains_edge(u, v))
                return adjList[u][v];
            return -1;
            
        }

        vector<pair<int, int>> primMST() {
            vector<pair<int, int>> mst;
            unordered_set<int> visited;
            priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int, int>>>> pq;

            if (adjList.empty())
                return mst;

            int start_vertex = adjList.begin()->first; // Start from first vertex
            visited.insert(start_vertex);

            // Add edges from the start vertex to the priority queue
            for (auto& neighbor : adjList[start_vertex]) {
                pq.push({ neighbor.second, {start_vertex,neighbor.first} });
            }

            while (!pq.empty()) {
                auto [weight, edge] = pq.top();
                pq.pop();
                auto [u,v] =edge;

                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    mst.push_back({ u, v});

                    // Add edges from the newly visited vertex to the priority queue
                    for (auto& neighbor : adjList[v]) {
                        if (visited.find(neighbor.first) == visited.end()){
                            pq.push({ neighbor.second, {v,neighbor.first} });
                        }
                        
                    }
                }
            }

            return mst;
        }
};