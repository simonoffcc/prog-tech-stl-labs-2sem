#include "Graph.h"

#include <iostream>

void userInterface(Graph);
void printVector(std::vector<int>);
void printMap(std::unordered_map<int, std::vector<int>>);

int main() {
    int vertexes;
    std::cout << "To create empty Graph, enter number of Vertexes: ";
    std::cin >> vertexes;

    try {
        Graph graph(vertexes);
        userInterface(graph);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}

void userInterface(Graph graph) {
    while (true) {
        std::cout << "\n>>> Select an action:\n";
        std::cout << "1. Add Vertex\n";
        std::cout << "2. Add Edge\n";
        std::cout << "3. Outgoing degrees at each vertex\n";
        std::cout << "4. Ingoing degrees at each vertex\n";
        std::cout << "5. Vertex with Max degree\n";
        std::cout << "6. Remove Multiples\n";
        std::cout << "7. Remove Cycles\n";
        std::cout << "8. Find Drains vertexes\n";
        std::cout << "9. Find Origins vertexes\n";
        std::cout << "10. Remove Vertex\n";
        std::cout << "11. Remove Edge\n";
        std::cout << "12. Print Graph\n";
        std::cout << "0. Quit\n\n";
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cerr << "Invalid input! Please enter a valid integer choice.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            int v;
            std::cout << "Enter vertex to add: ";
            if (!(std::cin >> v)) {
                std::cerr << "Invalid input!\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            graph.addVertex(v);
            break;
        }
        case 2: {
            int from, to;
            std::cout << "Enter source and destination vertexes to add Edge: ";
            if (!(std::cin >> from && std::cin >> to)) {
                std::cerr << "Invalid input!\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            graph.addEdge(from, to);
            break;
        }
        case 3: {
            std::cout << "Outgoing list of Vertexes:\n";
            printMap(graph.outgoingVertexes());
            break;
        }
        case 4: {
            std::cout << "Incoming list of Vertexes:\n";
            printMap(graph.incomingVertexes());
            break;
        }
        case 5: {
            //std::cout << "Vertex with maximum degree: " << graph.vertexWithMaxDegree() << "\n";
            std::cout << "Vertex with maximum degree: \n";
            printVector(graph.vertexesWithMaxDegree());
            break;
        }
        case 6: {
            graph.removeMultiples();
            std::cout << "Removed multiples.\n";
            break;
        }
        case 7: {
            graph.removeCycles();
            std::cout << "Removed cycles.\n";
            break;
        }
        case 8: {
            std::cout << "Drain(s):\n";
            printVector(graph.findDrains());
            break;
        }
        case 9: {
            std::cout << "Origin(s):\n";
            printVector(graph.findOrigins());
            break;
        }
        case 10: {
            int v;
            std::cout << "Enter vertex to remove: ";
            if (!(std::cin >> v)) {
                std::cerr << "Invalid input!\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            graph.removeVertex(v);
            break;
        }
        case 11: {
            int from, to;
            std::cout << "Enter source and destination vertex to remove Edge: ";
            if (!(std::cin >> from && std::cin >> to)) {
                std::cerr << "Invalid input!\n\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            graph.removeEdge(from, to);
            std::cout << "Edge removed: " << from << " !-> " << to << "\n";
            break;
        }
        case 12: {
            graph.print();
            break;
        }
        case 0: {
            std::cout << "Exiting program.\n";
            return;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void printVector(std::vector<int> vector) {
    for (int node : vector) {
        std::cout << node << " ";
    }
    std::cout << "\n";
}

void printMap(std::unordered_map<int, std::vector<int>> map) {
    for (const auto& entry : map) {
        int u = entry.first;
        std::cout << u << " : ";
        for (int node : entry.second) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }
}
