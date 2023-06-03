//
// Created by David Castro on 14/05/2023.
//

#include "GraphManager.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

GraphManager::GraphManager() {
    this->graph = Graph();
}

Graph GraphManager::getGraph() {
    return this->graph;
}

GraphManager::GraphManager(int type, int input){
    switch (type) {
        case 1:
            readToyGraphs(input);
            break;
        case 2:
            readRealWorld(input);
            break;
        case 3:
            readExtraFully(input);
            break;
        default:
            cout << "Invalid input" << endl;
            break;
    }
}


void GraphManager::readExtraFully(int input) {
    string filename;
    switch(input){
        case 1:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_25.csv";
            break;
        case 2:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_50.csv";
            break;
        case 3:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_75.csv";
            break;
        case 4:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_100.csv";
            break;
        case 5:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_200.csv";
            break;
        case 6:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_300.csv";
            break;
        case 7:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_400.csv";
            break;
        case 8:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_500.csv";
            break;
        case 9:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_600.csv";
            break;
        case 10:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_700.csv";
            break;
        case 11:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_800.csv";
            break;
        case 12:
            filename = "../dataset/Extra_Fully_Connected_Graphs/edges_900.csv";
            break;
        default:
            cout << "Invalid input" << endl;
            return;
    }

    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int node1 = stoi(tokens[0]);
        int node2 = stoi(tokens[1]);
        double weight = stod(tokens[2]);
        this->graph.addVertex(node1);
        this->graph.addVertex(node2);
        this->graph.addEdge(node1, node2, weight);
        this->graph.addEdge(node2, node1, weight);

    }
    file.close();
}

void GraphManager::readRealWorld(int input) {
    string filename_edges;
    string filename_nodes;
    switch (input) {
        case 1:
            filename_edges = "../dataset/Real-world Graphs/graph1/edges.csv";
            filename_nodes = "../dataset/Real-world Graphs/graph1/nodes.csv";
            break;
        case 2:
            filename_edges = "../dataset/Real-world Graphs/graph2/edges.csv";
            filename_nodes = "../dataset/Real-world Graphs/graph2/nodes.csv";
            break;
        case 3:
            cout<<"Here\n";
            filename_edges = "../dataset/Real-world Graphs/graph3/edges.csv";
            filename_nodes = "../dataset/Real-world Graphs/graph3/nodes.csv";
            break;
        default:
            cout << "Invalid input" << endl;
            return;
    }

    ifstream file_nodes(filename_nodes);
    string line_nodes;

    getline(file_nodes, line_nodes);
    while (getline(file_nodes, line_nodes)) {
        stringstream ss(line_nodes);

        string nodeId, lon, lat;
        getline(ss, nodeId, ',');
        getline(ss, lon, ',');
        getline(ss, lat, '\0');

        int id1 = stoi(nodeId);
        double lat2 = stod(lat);
        double lon2 = stod(lon);
        this->graph.addVertex(id1, lon2, lat2);
    }

    ifstream file_edges(filename_edges);
    string line_edges;

    getline(file_edges,line_edges);
    while (getline(file_edges, line_edges)) {
        stringstream ss(line_edges);

        string node1;
        string node2;
        string weight;
        getline(ss, node1, ',');
        getline(ss, node2, ',');
        getline(ss, weight, '\0');

        int node1_ = stoi(node1);
        int node2_ = stoi(node2);
        double weight_ = stod(weight);
        this->graph.addEdge(node1_, node2_, weight_);
        this->graph.addEdge(node2_, node1_, weight_);
    }

    file_nodes.close();
    file_edges.close();
}

void GraphManager::readToyGraphs(int input) {
    string filename;
    switch(input){
        case 1:
            filename = "../dataset/Toy-Graphs/shipping.csv";
            break;
        case 2:
            filename = "../dataset/Toy-Graphs/stadiums.csv";
            break;
        case 3:
            filename = "../dataset/Toy-Graphs/tourism.csv";
            break;
    }

    ifstream file(filename);
    if (!file.is_open())
        cout << "\nError in reading file!\n\n";

    string line;
    getline(file, line);
    if (input == 3) {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            int node1 = stoi(tokens[0]);
            int node2 = stoi(tokens[1]);
            double weight = stod(tokens[2]);
            string name1 = tokens[3];
            string name2 = tokens[4];
            this->graph.addVertex(node1, name1);
            this->graph.addVertex(node2, name2);
            this->graph.addEdge(node1, node2, weight);
            this->graph.addEdge(node2, node1, weight);
        }
    }
    else {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            int node1 = stoi(tokens[0]);
            int node2 = stoi(tokens[1]);
            double weight = stod(tokens[2]);
            this->graph.addVertex(node1);
            this->graph.addVertex(node2);
            this->graph.addEdge(node1, node2, weight);
            this->graph.addEdge(node2, node1, weight);
            // cout << node1 << ' ' << node2 << ' ' << weight << endl;
        }
    }
    file.close();
}





double GraphManager::tspBacktracking(Vertex *currentNode, Vertex *initialNode, int alreadyVisited, vector<int> &currentPath, vector<int> &minPath, double distanceSoFar, double minDistance, int &graphSize) {
    currentNode->setVisited(true);
    currentPath.push_back(currentNode->getId());        // in the first iteration, we add the initial node to the path, and so on
    alreadyVisited++;

    if (alreadyVisited == graphSize) {
        for (auto e : currentNode->getAdj()) {
            if (e->getDest() == initialNode) {              // returning to the initial node
                double totalDistance = distanceSoFar + e->getWeight();
                if (totalDistance < minDistance) {
                    minDistance = totalDistance;
                    minPath = currentPath;              // update minPath
                }
                break;
            }
        }
    }
    else {
        for (auto e : currentNode->getAdj()) {
            Vertex *adjNode = e->getDest();
            if (!adjNode->isVisited()) {
                double distanceNow = distanceSoFar + e->getWeight();
                minDistance = tspBacktracking(adjNode, initialNode, alreadyVisited, currentPath, minPath, distanceNow, minDistance, graphSize);
            }
        }
    }

    // "reduce" 1 iteration, once we reach the initial node
    currentNode->setVisited(false);
    currentPath.pop_back();     // pop the initialNode that was placed in currentPath twice
    alreadyVisited--;

    return minDistance;
}

void GraphManager::triangular() {
    clock_t start = clock();
    this->graph.triangularApproximation();
    clock_t end = clock();
    cout <<" Time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000.0 << " milliseconds" << endl;
}

double GraphManager::heuristic(int &graphSize) {
    Vertex *initialNode = graph.findVertex(0);
    Vertex *currentNode = graph.findVertex(0);
    vector<Edge*> path;
    double distance = 0.0;

    clock_t start = clock();
    this->graph.nearestNeighbor(initialNode, currentNode, path, graphSize, distance);

    for (auto itr : path) {
        cout << '[' << itr->getOrig()->getId() << ", " << itr->getDest()->getId() << "] -> ";
    }
    Edge* lastEdge = path.back();
    cout << '[' << lastEdge->getDest()->getId() << ", " << initialNode->getId() << ']' << endl;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "Time taken: " << duration << " milliseconds." << endl;
    cout << "-----------------------" << endl;

    return distance;
}

void GraphManager::deleteGraph() {
    for (auto vertex : graph.getVertexMap()) {
        for (Edge* edge : vertex.second->getAdj()) {
            delete edge;
        }
        vertex.second->getAdj().clear();
        delete vertex.second;
    }
    graph.deleteVertexMap();
    graph.deleteVertexSet();
}