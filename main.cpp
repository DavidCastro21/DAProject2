#include <iostream>
#include "src/GraphManager.h"


int main() {
    GraphManager manager = GraphManager(2, 3);
    //Graph graph = manager.getGraph();

    /*for (auto itr : graph.getVertexSet()) {
        cout << itr->getId() << ' ';
        cout << itr->getLatitude() << ' ';
        cout << itr->getLongitude() << endl;
    }*/

    // initialize matrix to 0 to keep the distances between each pair of nodes
    /*unsigned int graphSize = graph.getNumVertex();
    vector<vector<unsigned int>> distances(graphSize, vector<unsigned int>(graphSize, 0));

    // fill the matrix with the distances
    for (auto v : graph.getVertexSet()) {
        int sourceId = v->getId();
        for (auto e : v->getAdj()) {
            auto dest = e->getDest();
            int destId = dest->getId();
            distances[sourceId][destId] = e->getWeight();
        }
    }

    // Dynamically allocate a 2D array
    /*unsigned int** array = new unsigned int*[graphSize];
    for (int i = 0; i < graphSize; i++) {
        array[i] = new unsigned int[graphSize];
    }

    // Copy the elements from the vector of vectors to the 2D array
    for (unsigned int i = 0; i < graphSize; i++) {
        for (unsigned int j = 0; j < graphSize; j++) {
            array[i][j] = distances[i][j];
        }
    }*/

    /*vector<unsigned int> path;
    manager.tspBT(distances, graphSize, path);
     */

    return 0;
}


