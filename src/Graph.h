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
#include <stack>
#include "VertexEdge.h"
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
    void dfs(int id, vector<int> &path);
    void prim();
    int minWeight(vector<double>& weights, vector<bool> & visited);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    bool haveEdge(int id1, int id2);
    double getDistance(const vector<int>& path);

protected:
    int numVertex;
    unordered_map<int,Vertex*> vertexMap;
};



#endif /* DA_TP_CLASSES_GRAPH */