//
// Created by David Castro on 14/05/2023.
//

#ifndef DA_2ND_PROJECT_READFILES_H
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

class ReadFiles {
    Graph graph;
public:
    ReadFiles();
    ReadFiles(int type, int input);
    void readRealWorld(int input);

    void readExtraFully(int input);

    void readToyGraphs(int input);

    Graph getGraph();
};


#endif //DA_2ND_PROJECT_READFILES_H
