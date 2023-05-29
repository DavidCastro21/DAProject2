#include <iostream>
#include "src/GraphManager.h"


int main() {
    GraphManager manager = GraphManager(1, 1);
    Graph graph = manager.getGraph();

    for (auto itr : graph.getVertexSet()) {
        // cout << itr->getId() << ' ';
        // cout << itr->getAdj().size() << endl;
    }

    // initialize matrix to 0 to keep the distances between each pair of nodes
    unsigned int graphSize = graph.getNumVertex();
    // vector<vector<unsigned int>> distances(graphSize, vector<unsigned int>(graphSize, 0));

    // fill the matrix with the distances



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

    // vector<unsigned int> path;

    //unsigned int** matrix;
    unsigned int path[graphSize];

    unsigned int **distances = new unsigned int*[graphSize]; // Allocate memory for the rows

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
    }
    //distances = matrix;
    unsigned int result = manager.tspBT(distances, graphSize, path);


    // cout << result << endl;

    return 0;
}


