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
    if (findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id);
    vertexMap[id] = v1;
    return true;
}
bool Graph::addVertex(const int &id, double longitude, double latitude) {
    if(findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, longitude, latitude);
    vertexMap[id] = v1;
    return true;
}
bool Graph::addVertex(const int &id, string name) {
    if(findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, name);
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

void Graph::dfs(int id, const vector<int> &parent_, vector<bool> &visited, stack<int> &stack, vector<int> &path) {
    visited[id] = true;
    stack.push(id);
    while(!stack.empty()){
        int top = stack.top();
        stack.pop();
        path.push_back(top);
        for(int i = 0; i < parent_.size(); i++){
            if(parent_[i] == top && !visited[i]){
                visited[i] = true;
                stack.push(i);
            }
        }
    }
}
vector<pair<int,int>> Graph::prim(vector<int> &parents) {
    vector<double> weights(vertexMap.size(), numeric_limits<double>::max());
    vector<bool> visited(vertexMap.size(), false);
    int top = 0;
    weights[top] = 0.0;
    for(int i = 0; i<vertexMap.size()-1; i++ ){
        int min = minWeight(weights, visited);
        visited[min] = true;
        Vertex *v = vertexMap[min];
        if(v != nullptr){
            for(auto edge: v->getAdj()){
                if(!visited[edge->getDest()->getId()] && edge->getWeight() < weights[edge->getDest()->getId()]){
                    parents[edge->getDest()->getId()] = min;
                    weights[edge->getDest()->getId()] = edge->getWeight();
                }
            }
        }
    }
    vector<pair<int,int>> result;
    for(int i = 1; i< vertexMap.size(); i++){
        result.push_back(make_pair(parents[i], i));
    }
    return result;
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
    for(int i = 0; i<vertexMap[id1]->getAdj().size(); i++){
        if(vertexMap[id1]->getAdj()[i]->getDest()->getId() == id2){
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
    for(int i = 0; i< path.size();i++){
        int v1 = path[i];
        int v2 = path[i+1];
        if(!haveEdge(v1, v2)){
            result += haversine(vertexMap[v1]->getLatitude(), vertexMap[v1]->getLongitude(),vertexMap[v2]->getLatitude(),vertexMap[v2]->getLongitude());
            continue;
        }
        Vertex *v = vertexMap[v1];
        if (v != nullptr){
            for(auto edge: v->getAdj()){
                if(edge->getDest()->getId() == v2){
                    result += edge->getWeight();
                }
            }
        }
    }
    int final = path.back();
    if(haveEdge(final,path[0])){
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
    vector<int> parent_ (vertexMap.size(), -1);
    prim(parent_);
    vector<bool> visited(vertexMap.size(), false);
    stack<int> stack;
    vector<int> path;
    dfs(0, parent_, visited, stack, path);
    for(int i =0; i< path.size();i++){
        cout << path[i] << " ";
    }
    double distance = getDistance(path);
    cout <<"0" << endl<<"DISTANCE:: " << distance << endl;
    return distance;
}

// Path: src/GraphAlgorithms.cpp