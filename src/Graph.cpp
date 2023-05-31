// By: Gonçalo Leão

#include "Graph.h"
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

Graph::Graph() {
    this->numVertex = 0;
}

Graph::Graph(int nrVertex) {
    this->numVertex = nrVertex;
}

bool Graph::addVertex(const int &id) {
    if (vertexMap.find(id) == nullptr) { // id does not exist in map yet
        auto *v1 = new Vertex(id);
        vertexMap[id] = v1;
        return true;
    }
    return false;
}
bool Graph::addVertex(const int &id, double longitude, double latitude) {
    auto *v1 = new Vertex(id, longitude, latitude);
    vertexMap[id] = v1;
    return true;
}
bool Graph::addVertex(const int &id, string name) {
    if (vertexMap.find(id) == nullptr) { // id does not exist in map yet
        auto *v1 = new Vertex(id, name);
        vertexMap[id] = v1;
        return true;
    }
    return false;
}

bool Graph::addEdge(const int &sourc, const int &dest, double w) const {
    Vertex *v1 = findVertex(sourc);
    Vertex *v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;

    v1->addEdge(v2, w);
    return true;
}





int Graph::getNumVertex() const {
    return vertexMap.size();
}

const unordered_map<int, Vertex *> Graph::getVertexMap() const {
    return vertexMap;
}

Vertex *Graph::findVertex(const int &id) const {
    return vertexMap.at(id);
}

/*int Graph::findVertexIdx(const int &id) const {
    int i = 0;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it, ++i)
        if ((*it)->getId() == id)
            return i;
    return -1;
}*/


void Graph::resetVisited() {
    for (auto v : vertexMap)
        v.second->setVisited(false);
}

void Graph::resetDist() {
    for (auto v : vertexMap)
        v.second->setDist(0);
}

void Graph::resetPath() {
    for (auto v : vertexMap)
        v.second->setPath(nullptr);
}

// Path: src/GraphAlgorithms.cpp