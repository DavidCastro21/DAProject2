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


void Graph::resetVisited() {
    for (auto v : vertexSet)
        v->setVisited(false);
}

void Graph::resetDist() {
    for (auto v : vertexMap)
        v.second->setDist(0);
}

void Graph::resetPath() {
    for (auto v : vertexMap)
        v.second->setPath(nullptr);
}

void Graph::dfs(Vertex* initial, vector<int> &path) {
    initial->setVisited(true);
    cout << initial->getId() << " -> ";
    path.push_back(initial->getId());
    for (const auto &e: initial->getAdj()) {
        Vertex* w = e->getDest();
        if (!w->isVisited() && e->getOrig()->getId() == initial->getId()) {
            dfs(w,path);
        }
    }
}
Vertex * Graph::prim() {
    if (vertexMap.empty()) {
        return nullptr;
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
    vector<Vertex*> aux;

    // initialize priority queue
    MutablePriorityQueue<Vertex> q;
    q.insert(s);
    // process vertices in the priority queue
    while( ! q.empty() ) {
        auto v = q.extractMin();
        v->setVisited(true);
        for(auto &e : v->getAdj()) {
            Vertex* w = e->getDest();
            if (!w->isVisited()) {
                auto oldDist = w->getDist();
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);
                    if(v == vertexSet.front()){ //vai funcionar porque ao início todos os adj do vetor inicial vao ter o path como o edge entre o nó inicial e o nó do adj
                        aux.push_back(w);
                    }
                    if (oldDist == INT32_MAX) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    int count = 0;
    for(auto vertex: aux){
        if(vertex->getPath()->getOrig()==s) {
            cout<<vertex->getId()<<endl;
            count++;
        }
    }
    cout<<count<<endl;
    return nullptr;
}

int Graph::minWeight(vector<double> &weights, vector<bool> &visited) {
    double min = numeric_limits<double>::max();
    int min_index = -1;
    for(int i = 0; i<weights.size(); i++){
        if(!visited[i] && weights[i] < min){
            min = weights[i];
            min_index = i;
        }
    }
    return min_index;
}

bool Graph::haveEdge(int id1, int id2) {
    int index;
    for(int i = 0; i<vertexMap.size(); i++){
        if(vertexMap[i]->getId() == id1){
            index = i;
        }
    }
    for(auto edge: vertexMap[index]->getAdj()){
        if(edge->getDest()->getId() == id2){
            return true;
        }
    }
    return false;
}

double Graph::haversine(double lat1, double lon1, double lat2, double lon2) {
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
            result += haversine(vertexMap[v1]->getLatitude(), vertexMap[v1]->getLongitude(),vertexMap[v2]->getLatitude(),vertexMap[v2]->getLongitude());
            continue;
        }
        else {
            Vertex *v = vertexMap[v1];
            for(auto edge: v->getAdj()){
                if(edge->getDest()->getId() == v2){
                    result += edge->getWeight();
                    break;
                }
            }
        }
    }
    int final = path.back();
    if(!haveEdge(final,path[0])){
        result += haversine(vertexMap[final]->getLatitude(), vertexMap[final]->getLongitude(),vertexMap[path[0]]->getLatitude(),vertexMap[path[0]]->getLongitude());
    }
    else{
        Vertex *v = vertexMap[final];
        if (v != nullptr){
            for(auto edge: v->getAdj()){
                if(edge->getDest()->getId() == path[0]){
                    result += edge->getWeight();
                }
            }
        }
    }
    return result;
}


double Graph::triangularApproximation() {
    double result = 0;
    //vector<int> parent_ (vertexMap.size(), -1);
    Vertex* initial = prim();

    cout << "Preorder traversal of tree is \n";
    vector<bool> visited(vertexMap.size(), false);
    vector<int> preorder(vertexMap.size());
    resetVisited();
    dfs(vertexSet.front(), preorder);
    cout <<endl;
    result = getDistance(preorder);
    cout << "Distance: " << result << endl;
}

// Path: src/GraphAlgorithms.cpp