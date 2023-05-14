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
using namespace std;

class Graph {
protected:
    struct Edge{
        Edge();
        Edge(int dest);
        Edge(int dest, double weight);
        int dest;
        double weight;
    };

    struct Vertex{
        Vertex();
        Vertex(int id);
        Vertex(int id, double longitude, double latitude);
        Vertex(int id, string name);
        int id;
        string name;
        int dist = 0;
        double longitude = 0.0;
        double latitude = 0.0;
        bool visited = false;
        list<Edge> adj;
        Edge *path = nullptr;
        bool operator<(Vertex & vertex) const;
    };

    int numVertex;
    set<Vertex *> vertexSet;
public:
    Graph();
    Graph(int nrVertex);

    bool addVertex(const int &id);
    bool addVertex(const int &id, double longitude, double latitude);
    bool addVertex(const int &id, string name);
    bool addEdge(const int &sourc, const int &dest, double w);
    bool addEdge(const int &sourc, const int &dest);
    bool removeVertex(const int &id);

    int getNumVertex() const;
    set<Vertex *> getVertexSet() const;

    Vertex * findVertex(const int &id) const;
    int findVertexIdx(const int &id) const;

    void resetVisited();
    void resetDist();
    void resetPath();
};

#endif /* DA_TP_CLASSES_GRAPH */