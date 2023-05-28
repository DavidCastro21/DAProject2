//
// Created by David Castro on 14/05/2023.
//

#ifndef DA_2ND_PROJECT_READFILES_HF
#define DA_2ND_PROJECT_READFILES_H

#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <list>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class GraphManager {
    Graph graph;
public:
    GraphManager();
    GraphManager(int type, int input);
    Graph getGraph();

    void readRealWorld(int input);
    void readExtraFully(int input);
    void readToyGraphs(int input);

    vector<Vertex*> preOrderPath(Graph graph);
    void tspBTRec(const unsigned int **dists, unsigned int n, unsigned int curIndex, unsigned int curDist, unsigned int curPath[], unsigned int &minDist, unsigned int path[]);
    unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]);
};


#endif //DA_2ND_PROJECT_READFILES_H