#include "Graph.h"

#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>


Graph::Graph(int numVertexes) {
    if (!numVertexes || numVertexes <= 0) {
        throw std::logic_error("Error! Invalid vertex number!");
    }
    for (int i = 1; i <= numVertexes; ++i) {
        adjacencyList[i] = std::vector<int>();
    }
}

bool Graph::isEmpty() const {
    return adjacencyList.empty();
}

int Graph::countVertexes() const {
    return adjacencyList.size();
}

bool Graph::hasVertex(int node) const {
    return adjacencyList.find(node) != adjacencyList.end();
}

bool Graph::hasEdge(int from, int to) const {
    if (hasVertex(from)) {
        const std::vector<int>& neighbors = adjacencyList.at(from);
        for (int neighbor : neighbors) {
            if (neighbor == to) {
                return true;
            }
        }
    }
    return false;
}

void Graph::addVertex(int node) {
    if (adjacencyList.find(node) == adjacencyList.end()) {
        adjacencyList[node] = std::vector<int>();
    }
    else {
        std::cerr << "Vertex is already exists.\n";
    }
}

void Graph::addEdge(int from, int to) {
    if (adjacencyList.find(from) != adjacencyList.end() && adjacencyList.find(to) != adjacencyList.end()) {
        adjacencyList[from].push_back(to);
        std::cout << "Edge added: " << from << " -> " << to << "\n";
    }
    else {
        std::cerr << "There is no \"from\" or \"to\" vertexes in graph!\n";
    }
}

void Graph::removeVertex(int node) {
    if (adjacencyList.find(node) != adjacencyList.end()) {
        adjacencyList.erase(node);
        for (auto& entry : adjacencyList) {
            entry.second.erase(std::remove(entry.second.begin(), entry.second.end(), node), entry.second.end());
        }
    }
    else {
        std::cerr << "There is no vertex with this key.\n";
    }
}

void Graph::removeEdge(int from, int to) {
    if (adjacencyList.find(from) != adjacencyList.end()) {
        auto& neighbors = adjacencyList[from];
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), to), neighbors.end());
    }
    else {
        std::cerr << "There is no \"from\" or \"to\" vertexes in graph!\n";
    }
}

void Graph::print() const {
    if (this->isEmpty()) {
        std::cerr << "Graph is empty.\n";
        return;
    }
    
    for (const auto& entry : adjacencyList) {
        int node = entry.first;
        const std::vector<int>& neighbors = entry.second;

        std::cout << node << " -> ";
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}

std::vector<int> Graph::vertexesWithMaxDegree() const {
    int maxDegree = -1;
    std::vector<int> verticesWithMaxDegree;

    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        int outDegree = entry.second.size();

        int inDegree = 0;
        for (const auto& entry : adjacencyList) {
            if (u != entry.first) {
                inDegree += std::count(entry.second.begin(), entry.second.end(), u);
            }
        }

        int totalDegree = inDegree + outDegree;

        if (totalDegree > maxDegree) {
            maxDegree = totalDegree;
            verticesWithMaxDegree.clear();
            verticesWithMaxDegree.push_back(u);
        }
        else if (totalDegree == maxDegree) {
            verticesWithMaxDegree.push_back(u);
        }
    }

    return verticesWithMaxDegree;
}

std::unordered_map<int, std::vector<int>> Graph::outgoingVertexes() const {
    std::unordered_map<int, std::vector<int>> outgoing;
    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        for (int node : entry.second) {
            outgoing[u].push_back(node);
        }
    }
    return outgoing;
}

std::unordered_map<int, std::vector<int>> Graph::incomingVertexes() const {
    std::unordered_map<int, std::vector<int>> incoming;
    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        for (const auto& other_entry : adjacencyList) {
            int node = other_entry.first;
            for (int neighbor : other_entry.second) {
                if (neighbor == u) {
                    incoming[u].push_back(node);
                }
            }
        }
    }
    return incoming;
}

void Graph::removeMultiples() {
    for (auto& entry : adjacencyList) {
        int u = entry.first;
        std::vector<int>& neighbors = entry.second;
        std::sort(neighbors.begin(), neighbors.end());
        neighbors.erase(std::unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }
}

std::vector<int> Graph::findDrains() const {
    std::vector<int> drains;
    std::unordered_set<int> vertexes;

    for (const auto& entry : adjacencyList) {
        vertexes.insert(entry.first);
    }

    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        bool isDrain = true;

        for (int node : vertexes) {
            if (u != node) {
                if (std::find(entry.second.begin(), entry.second.end(), node) != entry.second.end())
                {
                    isDrain = false;
                    break;
                }
            }
        }

        if (isDrain) {
            drains.push_back(u);
        }
    }

    return drains;
}

std::vector<int> Graph::findOrigins() const {
    std::vector<int> origins;
    std::unordered_set<int> vertexes;

    for (const auto& entry : adjacencyList) {
        vertexes.insert(entry.first);
    }

    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        bool isOrigin = true;

        for (int node : vertexes) {
            if (u != node) 
            {
                if (std::find_if(
                    adjacencyList.begin(), adjacencyList.end(),
                    [u, node](const std::pair<int, std::vector<int>>& p) 
                    {
                        return p.first != u && std::find(p.second.begin(), p.second.end(), u) != p.second.end();
                    }) != adjacencyList.end()
                ) {
                    isOrigin = false;
                    break;
                }
            }
        }

        if (isOrigin) {
            origins.push_back(u);
        }
    }

    return origins;
}

void Graph::removeCycles() {
    std::unordered_set<int> visited;
    std::unordered_set<int> onPath;

    for (const auto& entry : adjacencyList) {
        int u = entry.first;
        if (!visited.count(u) && hasCycle(u, visited, onPath)) {
            removeCycle(u, onPath);
        }
    }
}

bool Graph::hasCycle(int u, std::unordered_set<int>& visited, std::unordered_set<int>& onPath) {
    visited.insert(u);
    onPath.insert(u);

    for (int neighbor : adjacencyList[u]) {
        if (onPath.count(neighbor) || (!visited.count(neighbor) && hasCycle(neighbor, visited, onPath))) {
            return true;
        }
    }

    onPath.erase(u);
    return false;
}

void Graph::removeCycle(int u, std::unordered_set<int>& onPath) {
    std::unordered_set<int> cycle;
    for (int vertex : onPath) {
        cycle.insert(vertex);
    }

    for (int neighbor : adjacencyList[u]) {
        if (cycle.count(neighbor)) {
            auto& neighbors = adjacencyList[u];
            neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), neighbor), neighbors.end());
        }
    }

    onPath.clear();
}
