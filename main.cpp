#include <iostream>
#include <ctime>
#include "src/GraphManager.h"


int main() {
    GraphManager manager = GraphManager(1, 1);

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



    // Calculate the duration in milliseconds

    Graph newGraph = manager.getGraph();
    newGraph.triangularApproximation();
    return 0;
}