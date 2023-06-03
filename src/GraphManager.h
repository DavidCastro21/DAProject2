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
    /**
     * Complexity: O(1)
     * @brief Default constructor
     */
    GraphManager();
    /**
     * Complexity: O(1)
     * @brief Constructor that reads the graph from a file
     * @param type - 0 for real world, 1 for extra fully, 2 for toy graphs
     * @param input - 0 for 1st graph, 1 for 2nd graph, 2 for 3rd graph
     */
    GraphManager(int type, int input);
    /**
     * Complexity: O(1)
     * @brief Returns the graph
     * @return the graph
     */
    Graph getGraph();
    /**
     * Complexity: O(|V| + |E|)
     * @brief Reads the graph from a file
     * @param input - 1 for 1st graph, 2 for 2nd graph, 3 for 3rd graph
     */
    void readRealWorld(int input);
    /**
     * Complexity: O(|E|)
     * @brief Reads the graph from a file
     * @param input - read the input-th file from the extra fully connected graphs from 1 to 12
     */
    void readExtraFully(int input);

    /**
     * Complexity: O(|V| + |E|)
     * @brief Reads the graph from a file
     * @param input - 1 for 1st graph, 2 for 2nd graph, 3 for 3rd graph
     */
    void readToyGraphs(int input);

    /**
     * Complexity: O(V!)
     * @brief Calculates the shortest path between all the nodes of the graph
     * @param currentNode - current node
     * @param initialNode - initial node
     * @param alreadyVisited - number of nodes already visited
     * @param currentPath - current path
     * @param minPath - minimum path
     * @param distanceSoFar - distance so far
     * @param minDistance - minimum distance
     * @param graphSize - size of the graph
     * @return the minimum distance
     */
    double tspBacktracking(Vertex *currentNode, Vertex *initialNode, int alreadyVisited, vector<int> &currentPath,vector<int> &minPath, double distanceSoFar, double minDistance, int &graphSize);

    /**
     * Complexity: O(|V| + |E|)
     * @brief Calculates the shortest path between all the nodes of the graph using triangular approximation algorithm
     */
    void triangular();
    /**
     * Complexity: O(V^2)
     * @brief Calculates the shortest path between all the nodes of the graph using nearest neighbor algorithm
     * @param graphSize - size of the graph
     * @return the heuristic value
     */
    double heuristic(int &graphSize);
};

#endif //DA_2ND_PROJECT_READFILES_H
