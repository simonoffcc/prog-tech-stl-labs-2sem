#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

class Graph {
    public:
        Graph(int);
        void addVertex(int);
        void addEdge(int from, int to);
        void removeVertex(int);
        void removeEdge(int from, int to);
        void print() const;
        std::vector<int> vertexesWithMaxDegree() const;
        void removeMultiples();
        void removeCycles();
        std::unordered_map<int, std::vector<int>> outgoingVertexes() const;
        std::unordered_map<int, std::vector<int>> incomingVertexes() const;
        std::vector<int> findDrains() const;
        std::vector<int> findOrigins() const;
        
    private:
        std::unordered_map<int, std::vector<int>> adjacencyList;
        int countVertexes() const;
        bool isEmpty() const;
        bool hasVertex(int node) const;
        bool hasEdge(int from, int to) const;
        bool hasCycle(int u, std::unordered_set<int>& visited, std::unordered_set<int>& onPath);
        void removeCycle(int u, std::unordered_set<int>& onPath);
};

#endif
