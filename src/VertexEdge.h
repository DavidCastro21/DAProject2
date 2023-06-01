//
// Created by Utilizador on 28/05/2023.
//

#ifndef UNTITLED1_VERTEXEDGE_H
#define UNTITLED1_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include "MutablePriorityQueue.h"

using namespace std;

class Edge;

class Vertex{
public:
    Vertex();
    Vertex(int id);
    Vertex(int id, double longitude, double latitude);
    Vertex(int id, string name);

    int getId() const;
    string getName() const;
    int getDist() const;
    double getLatitude() const;
    double getLongitude() const;
    bool isVisited() const;
    Edge* getPath() const;
    vector<Edge*> getAdj() const;
    void addEdge(Vertex* dest, double weight);
    void setId(int id);
    void setName(string name);
    void setDist(int dist);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setVisited(bool visited);
    void setPath(Edge *path);
    bool operator<(Vertex & vertex) const;
    friend class MutablePriorityQueue<Vertex*>;
    int queueIndex = 0;

protected:
    int id;
    string name;
    int dist = 0;
    double longitude = 0.0;
    double latitude = 0.0;
    bool visited = false;
    vector<Edge*> adj;
    Edge *path = nullptr;
};

class Edge {
public:
    Edge();
    Edge(Vertex* dest);
    Edge(Vertex* dest, double weight);
    Edge(Vertex* origin, Vertex* dest, double weight);

    Vertex* getDest() const;
    double getWeight() const;
    void setDest(Vertex* dest);
    void setWeight(double weight);
    Vertex* getOrig() const;
    void setOrig(Vertex* orig);
private:
    Vertex* orig;
    Vertex* dest;
    double weight;
};

#endif //UNTITLED1_VERTEXEDGE_H
