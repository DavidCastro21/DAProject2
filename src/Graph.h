// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <map>
#include "VertexEdge.h"
#include <cmath>


using namespace std;

class Graph {
public:
    Graph();
    explicit Graph(int nrVertex);

    bool addVertex(const int &id);
    bool addVertex(const int &id, double longitude, double latitude);
    bool addVertex(const int &id, string name);
    bool addEdge(const int &sourc, const int &dest, double w) const;
    bool removeVertex(const int &id);

    int getNumVertex() const;
    const unordered_map<int, Vertex *> getVertexMap() const;

    Vertex * findVertex(const int &id) const;
    // int findVertexIdx(const int &id) const;

    void resetVisited();
    void resetDist();
    void resetPath();

    double triangularApproximation();
    void dfs(const vector<Edge*> &mst, Vertex* v, vector<bool> &visited, vector<int> &path);
    vector<Edge*> prim();
    int minWeight(vector<double>& weights, vector<bool> & visited);
    double haversine(Vertex *initialNode, Vertex *finalNode);
    bool haveEdge(int id1, int id2);
    double getDistance(const vector<int>& path);
    double nearestNeighbor(Vertex* &initialNode, Vertex* &currentNode, vector<Edge*> &path, int &graphSize, double &distance, bool allVisited = false);
    int nrNodesAlreadyVisited(unordered_map<int, Vertex*> vertexMap);
    void findOdds();
    void perfectMatching();
    void Christofides();
    double findBestPath(int start);
    void euler_tour(int start, vector<int> &path);
    void make_hamiltonian(vector<int> &path, double &length);

        protected:
    int numVertex;
    unordered_map<int,Vertex*> vertexMap;
    map<int, vector<Vertex*>> mst_adj;
    vector<int> odds;
    map<int, vector<Vertex*>> adj;
    map<int, double> weights;
};

class WeightCompare{
    public:
        bool operator()(const Edge* e1, const Edge * e2) const{
            return e1->getWeight() > e2->getWeight();
    }
};



#endif /* DA_TP_CLASSES_GRAPH */