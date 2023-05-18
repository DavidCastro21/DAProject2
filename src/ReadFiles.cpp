//
// Created by David Castro on 14/05/2023.
//

#include "ReadFiles.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;



ReadFiles::ReadFiles() {
    this->graph = Graph();
}

Graph ReadFiles::getGraph() {
    return this->graph;
}

void ReadFiles::readExtraFully(int input) {
    string filename;
    switch(input){
        case 1:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_25.csv";
            break;
    case 2:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_50.csv";
            break;
    case 3:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_75.csv";
            break;
    case 4:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_100.csv";
            break;
    case 5:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_200.csv";
            break;
    case 6:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_300.csv";
            break;
    case 7:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_400.csv";
            break;
    case 8:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_500.csv";
            break;
    case 9:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_600.csv";
            break;
    case 10:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_700.csv";
            break;
    case 11:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_800.csv";
            break;
    case 12:
            filename = "dataset/Extra_Fully_Connected_Graphs/edges_900.csv";
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
        int weight = stoi(tokens[2]);
        this->graph.addVertex(node1);
        this->graph.addVertex(node2);
        this->graph.addEdge(node1, node2, weight);
    }
    file.close();
}

void ReadFiles::readRealWorld(int input) {
    string filename_edges;
    string filename_nodes;
    switch (input) {
        case 1:
            filename_edges = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph1/edges.csv";
            filename_nodes = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph1/nodes.csv";
            break;
        case 2:
            filename_edges = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph2/edges.csv";
            filename_nodes = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph2/nodes.csv";
            break;
        case 3:
            filename_edges = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph3/edges.csv";
            filename_nodes = "/Users/davidcastro/Desktop/DAProject2_2023/dataset/Real-world Graphs/graph3/nodes.csv";
            break;
        default:
            cout << "Invalid input" << endl;
            return;
    }
    ifstream file_nodes(filename_nodes);
    string line_nodes;
    int i = 0;
    getline(file_nodes, line_nodes);
    while (getline(file_nodes, line_nodes)) {
        stringstream ss(line_nodes);
        string nodeid, lon, lat;
        getline(ss, nodeid, ',');
        cout << nodeid << endl;
        getline(ss, lon, ',');
        cout << nodeid << lon << endl;
        getline(ss, lat, ',');
        cout << nodeid << lon << lat << endl;
        int id1 = stoi(nodeid);
        cout << i << endl;
        double lat2 = stod(lat);
        cout << lat2 << endl;
        double lon2 = stod(lon);
        cout << lon2 << endl;
        this->graph.addVertex(id1, lat2, lon2);
    }
    ifstream file_edges(filename_edges);
    string line_edges;
    while (getline(file_edges, line_edges)) {
        stringstream ss(line_edges);
        string node1;
        string node2;
        string weight;
        getline(ss, node1, ',');
        getline(ss, node2, ',');
        getline(ss, weight, ',');
        int node1_ = stoi(node1);
        int node2_ = stoi(node2);
        double weight_ = stod(weight);
        this->graph.addEdge(node1_, node2_, weight_);
    }
    file_nodes.close();
    file_edges.close();

}

void ReadFiles::readToyGraphs(int input) {
    string filename;
    switch(input){
        case 1:
            filename = "dataset/Toy_Graphs/shipping.csv";
            break;
        case 2:
            filename = "dataset/Toy_Graphs/stadiums.csv";
            break;
        case 3:
            filename = "dataset/Toy_Graphs/airports.csv";
            break;
    }
    ifstream file(filename);
    string line;
    if(input == 3){
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            int node1 = stoi(tokens[0]);
            int node2 = stoi(tokens[1]);
            int weight = stoi(tokens[2]);
            string name1 = tokens[3];
            string name2 = tokens[4];
            this->graph.addVertex(node1, name1);
            this->graph.addVertex(node2, name2);
            this->graph.addEdge(node1, node2, weight);
        }
    }
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int node1 = stoi(tokens[0]);
        int node2 = stoi(tokens[1]);
        int weight = stoi(tokens[2]);
        this->graph.addVertex(node1);
        this->graph.addVertex(node2);
        this->graph.addEdge(node1, node2, weight);
    }
    file.close();

}