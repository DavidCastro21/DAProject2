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
    void deleteVertexMap();
    void deleteVertexSet();

    int getNumVertex() const;
    const unordered_map<int, Vertex *> getVertexMap() const;

    Vertex * findVertex(const int &id) const;
    // int findVertexIdx(const int &id) const;

    void resetVisited();
    void resetDist();
    void resetPath();

    double triangularApproximation();
    void dfs(vector<int> &path, double &distance, bool nextOne, Vertex* source, double &lat, double &lon);
    void prim();
    int minWeight(vector<double>& weights, vector<bool> & visited);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    Edge* haveEdge(int id1, int id2);
    double getDistance(const vector<int>& path);
    map<int, vector<Vertex*>> mst_adj;
    void transformMapToVertex();
protected:
    int numVertex;
    vector<Vertex*> vertexSet;
    unordered_map<int,Vertex*> vertexMap;
};

class WeightCompare{
    public:
        bool operator()(const Edge* e1, const Edge * e2) const{
            return e1->getWeight() > e2->getWeight();
    }
};



#endif /* DA_TP_CLASSES_GRAPH */