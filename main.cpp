#include <iostream>
#include <ctime>
#include "src/GraphManager.h"


int main() {
    GraphManager manager = GraphManager(1, 1);
    Graph graph = manager.getGraph();

    int graphSize = graph.getNumVertex();


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

    clock_t start = clock();

    Vertex* initialNode = graph.findVertex(0);
    vector<int> currentPath;
    vector<int> minPath;

    double result = manager.tspBacktracking(initialNode, initialNode, 0, currentPath, minPath, 0.0, 10000000.0, graphSize);
    cout << result << endl;

    clock_t end = clock();

    // Calculate the duration in milliseconds
    double duration = double(end - start) / CLOCKS_PER_SEC * 1000.0;

    // Print the duration
    cout << "Time taken: " << duration << " milliseconds." << endl;

    return 0;
}