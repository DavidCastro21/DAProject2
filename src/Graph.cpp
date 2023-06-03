// By: Gonçalo Leão

#include "Graph.h"
#include "MutablePriorityQueue.h"
#include <limits>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <cmath>

using namespace std;

Graph::Graph() {
    this->numVertex = 0;
}

Graph::Graph(int nrVertex) {
    this->numVertex = nrVertex;
}

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id);
    vertexSet.push_back(v1);
    vertexMap[id] = v1;
    return true;
}
bool Graph::addVertex(const int &id, double longitude, double latitude) {
    if(findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, longitude, latitude);
    vertexSet.push_back(v1);
    vertexMap.insert(make_pair(id, v1));
    return true;
}
bool Graph::addVertex(const int &id, string name) {
    if(findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, name);
    vertexSet.push_back(v1);
    vertexMap[id] = v1;
    return true;
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
    auto it = vertexMap.find(id);
    if (it == vertexMap.end())
        return nullptr;
    return it->second;
}

/*int Graph::findVertexIdx(const int &id) const {
    int i = 0;
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it, ++i)
        if ((*it)->getId() == id)
            return i;
    return -1;
}*/



void Graph::dfs(unordered_map<Vertex*,vector<Edge*>>& mst, Vertex* v, vector<bool> &visited, vector<int> &path) {
    visited[v->getId()] = true;
    cout << v->getId() << " -> ";
    path.push_back(v->getId());
    for (const auto &e: mst[v]) {
        if (!visited[e->getDest()->getId()]) {
            dfs(mst, e->getDest(), visited, path);
        }
    }

}

unordered_map<Vertex*,vector<Edge*>> Graph::prim() {
    unordered_map<Vertex*,vector<Edge*>> mst;
    priority_queue<Vertex*, vector<Vertex*>, WeightCompare> q;
/*
    vector<bool> visited(vertexMap.size(), false);
    vector<Vertex*> parent;

    Vertex* v1 = this->vertexMap[0];

    for(const auto &e: v1->getAdj()){
        a.push(e);
    }
    visited[v1->getId()] = true;


    while (!a.empty()) {
        Edge* e = a.top();
        a.pop();
        Vertex* v = e->getDest();
        Vertex* u = e->getOrig();
        if (visited[v->getId()]) {
            continue;
        }
        visited[v->getId()] = true;
        mst.push_back(e);
        mst_adj[u->getId()].push_back(v);
        mst_adj[v->getId()].push_back(u);
        for (const auto parent: v->getAdj()) {
            if (!visited[parent->getDest()->getId()]) {
                a.push(parent);
            }
        }
    }
    return mst;
    */

    //=======================================================================
    vector<int> ids;


    if (vertexSet.empty()) {
        return mst;
    }

    // Reset auxiliary info
    for(auto v : vertexSet) {
        v->setDist(INT32_MAX);
        v->setPath(nullptr);
        v->setVisited(false);
    }

    // start with an arbitrary vertex
    Vertex* s = vertexSet.front();
    s->setDist(0);


    q.push(s);
    while(!q.empty()){
        Vertex* x = q.top();
        q.pop();
        if(x->isVisited()) continue;
        x->setVisited(true);
        for(auto e: x->getAdj()){
            if(!e->getDest()->isVisited() && e->getWeight()<e->getDest()->getDist()){
                e->getDest()->setPath(e);
                e->getDest()->setDist(e->getWeight());
                q.push(e->getDest());
            }
        }
    }

    for(auto vertex : vertexSet){
        if(vertex->getId()!=0){
            Edge* e = vertex->getPath();
            Vertex* origin = e->getOrig();
            mst[origin].push_back(e);
            mst[vertex].push_back(e->getReverse());
        }
    }
    return mst;
}


bool Graph::haveEdge(int id1, int id2) {
    for(auto edge: vertexMap[id1]->getAdj()){
        if(edge->getDest()->getId() == id2){
            return true;
        }
    }
    return false;
}



double Graph::haversine(Vertex *initialNode, Vertex *finalNode) {
    double lat1 = initialNode->getLatitude();
    double lon1 = initialNode->getLongitude();
    double lat2 = finalNode->getLatitude();
    double lon2 = finalNode->getLongitude();

    double R = 6371e3; // metres
    double phi1 = lat1 * M_PI/180; // φ, λ in radians
    double phi2 = lat2 * M_PI/180;
    double deltaPhi = (lat2-lat1) * M_PI/180;
    double deltaLambda = (lon2-lon1) * M_PI/180;

    double a = sin(deltaPhi/2) * sin(deltaPhi/2) +
               cos(phi1) * cos(phi2) *
               sin(deltaLambda/2) * sin(deltaLambda/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    double d = R * c; // in metres
    return d;
}

double Graph::getDistance(const vector<int> &path) {
    double result = 0.0;
    for(int i = 0; i < path.size() - 1 ;i++){
        int v1 = path[i];
        int v2 = path[i+1];
        if(!haveEdge(v1, v2)){
            result += haversine(vertexMap[v1], vertexMap[v2]);
            continue;
        }
        for(auto edge: vertexMap[v1]->getAdj()){
            if(edge->getDest()->getId() == v2){
                result += edge->getWeight();
                break;
            }
        }
    }
    int final = path.back();
    if(!haveEdge(final,path[0])){
        result += haversine(vertexMap[final], vertexMap[path[0]]);
    }
    else{
        for(auto edge: vertexMap[final]->getAdj()){
            if(edge->getDest()->getId() == path[0]){
                result += edge->getWeight();
            }
        }
    }
    return result;
}


double Graph::triangularApproximation() {
    double result = 0;
    //vector<int> parent_ (vertexMap.size(), -1);
    cout << "starting" << endl;
    clock_t begin = clock();
    unordered_map<Vertex*,vector<Edge*>> mst = prim();
    clock_t end = clock();
    cout << "Prim's algorithm time: " << double(end - begin) / CLOCKS_PER_SEC << endl;
    cout << "Preorder traversal of tree is \n";
    vector<bool> visited(vertexMap.size(), false);
    vector<int> preorder;
    dfs(mst, findVertex(0), visited, preorder);
    cout <<"0" <<endl;
    clock_t begin2 = clock();
    result = getDistance(preorder);
    clock_t end2 = clock();
    cout << "Distance calculation time: " << double(end2 - begin2) / CLOCKS_PER_SEC << endl;
    cout << "Distance: " << result << endl;
}

int Graph::nrNodesAlreadyVisited(unordered_map<int, Vertex*> vertexMap) {
    int count = 0;
    for (auto itr : vertexMap) {
        if (itr.second->isVisited())
            count++;
    }
    return count;
}

double Graph::nearestNeighbor(Vertex* &initialNode, Vertex* &currentNode, vector<Edge*> &path, int &graphSize, double &distance, bool allVisited) {
    if (nrNodesAlreadyVisited(vertexMap) == graphSize) {    // all nodes already visited
        allVisited = true;
    }
    if (allVisited) {
        double lastDistance = haversine(currentNode, initialNode);
        distance += lastDistance;

        return distance;
    }
    currentNode->setVisited(true);

    Edge *minEdge = nullptr;
    double minEdgeWeight = numeric_limits<double>::max();
    for (auto e : currentNode->getAdj()) {
        if (!e->getDest()->isVisited() && e->getWeight() < minEdgeWeight) {
            minEdge = e;
            minEdgeWeight = e->getWeight();
        }
    }

    if (minEdge) {
        distance += minEdgeWeight;
        path.push_back(minEdge);
        currentNode = minEdge->getDest();
    }
    else
        return distance;

    return nearestNeighbor(initialNode, currentNode, path, graphSize, distance, allVisited);
}
void Graph::deleteVertexMap(){
    vertexMap.clear();
}

void Graph::deleteVertexSet() {
    vertexSet.clear();
}

// Path: src/GraphAlgorithms.cpp

