// By: Gonçalo Leão

#include "Graph.h"
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

Graph::Graph() {
    this->numVertex = 0;
}
Graph:: Edge::Edge() {
    this->dest = INT32_MAX;
    this->weight = 0;
}
Graph:: Edge::Edge(int dest, double weight) {
    this->dest = dest;
    this->weight = weight;
}
Graph:: Edge::Edge(int dest) {
    this->dest = dest;
    this->weight = 1;
}
Graph:: Vertex::Vertex() {
    this->id = 0;
    this->dist = 0;
    this->visited = false;
    this->path = nullptr;
}
Graph:: Vertex::Vertex(int id) {
    this->id = id;
    this->visited = false;
    this->path = nullptr;
}
Graph:: Vertex::Vertex(int id, double longitude, double latitude) {
    this->id = id;
    this->longitude = longitude;
    this->latitude = latitude;
    this->visited = false;
    this->path = nullptr;
}
Graph:: Vertex::Vertex(int id, string name) {
    this->id = id;
    this->name = std::move(name);
    this->visited = false;
    this->path = nullptr;
}
bool Graph:: Vertex::operator<(Vertex & vertex) const {
    return this->id < vertex.id;
}

Graph::Graph(int nrVertex) {
    this->numVertex = nrVertex;
}

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id);
    vertexSet.insert(v1);
    return true;
}
bool Graph::addVertex(const int &id, double longitude, double latitude) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, longitude, latitude);
    vertexSet.insert(v1);
    return true;
}
bool Graph::addVertex(const int &id, string name) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, std::move(name));
    vertexSet.insert(v1);
    return true;
}

bool Graph::addEdge(const int &sourc, const int &dest, double w) const {
    Vertex *v1 = findVertex(sourc);
    Vertex *v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->adj.insert(v1->adj.end(), Edge(dest, w));
    return true;
}


bool Graph::removeVertex(const int &id) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it) {
        if ((*it)->id == id) {
            vertexSet.erase(it);
            return true;
        }
    }
    return false;
}


int Graph::getNumVertex() const {
    return vertexSet.size();
}

set<Graph::Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Graph::Vertex *Graph::findVertex(const int &id) const {
    for (auto v : vertexSet)
        if (v->id == id)
            return v;
    return nullptr;
}

int Graph::findVertexIdx(const int &id) const {
    int i = 0;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it, ++i)
        if ((*it)->id == id)
            return i;
    return -1;
}


void Graph::resetVisited() {
    for (auto v : vertexSet)
        v->visited = false;
}

void Graph::resetDist() {
    for (auto v : vertexSet)
        v->dist = 0;
}

void Graph::resetPath() {
    for (auto v : vertexSet)
        v->path = nullptr;
}

// Path: src/GraphAlgorithms.cpp