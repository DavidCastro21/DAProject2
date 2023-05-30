#include <iostream>
#include "src/GraphManager.h"


int main() {
    GraphManager manager = GraphManager(1, 1);
    Graph graph = manager.getGraph();


    /* unsigned int **distances = new unsigned int*[graphSize]; // Allocate memory for the rows

    for (unsigned int i = 0; i < graphSize; i++) {
        distances[i] = new unsigned int[graphSize]; // Allocate memory for each row (columns)
        for (unsigned int j = 0; j < graphSize; j++) {
            distances[i][j] = 0;
        }
    }
    for (auto v : graph.getVertexSet()) {
        unsigned int sourceId = v->getId();
        for (auto e : v->getAdj()) {
            auto dest = e->getDest();
            unsigned int destId = dest->getId();
            distances[sourceId][destId] = e->getWeight();
        }
    }*/


    int maxId = INT32_MIN;
    for (auto itr : graph.getVertexSet()) {
        if (itr->getId() > maxId) {
            maxId = itr->getId();
        }
    }
    // int alreadyVisited = 0;
    Vertex* initialNode = graph.findVertex(0);
    vector<int> currentPath;
    vector<int> minPath;
    // vector<bool> visited;
    bool visited[maxId];
    // double distSoFar = 0.0;
    // double minDist = std::numeric_limits<double>::max();
    double result = manager.tspBacktracking(initialNode, initialNode, 0, visited, currentPath, minPath, 0.0, std::numeric_limits<double>::max());
    cout << "shipping: " << result << endl;

    return 0;
}


