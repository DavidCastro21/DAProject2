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
    vertexMap[id] = v1;
    return true;
}
bool Graph::addVertex(const int &id, double longitude, double latitude) {
    if(findVertex(id) != nullptr)
        return false;
    auto *v1 = new Vertex(id, longitude, latitude);
    vertexMap.insert(make_pair(id, v1));
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

void Graph::dfs(const vector<Edge*> &mst, Vertex* v, vector<bool> &visited, vector<int> &path) {
    visited[v->getId()] = true;
    cout << v->getId() << " -> ";
    path.push_back(v->getId());
    for (const auto &neighborId: mst_adj[v->getId()]) {
        if (!visited[neighborId->getId()]) {
            dfs(mst,vertexMap[neighborId->getId()], visited, path);
        }
    }
}
vector<Edge*> Graph::prim() {
    vector<Edge*> mst;
    mst_adj.clear();
    priority_queue<Edge*, vector<Edge*>, WeightCompare> q;

    vector<bool> visited(vertexMap.size(), false);
    vector<Vertex*> parent;

    Vertex* v1 = this->vertexMap[0];

    for(const auto &e: v1->getAdj()){
        q.push(e);
    }
    visited[v1->getId()] = true;


    while (!q.empty()) {
        Edge* e = q.top();
        q.pop();
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
                q.push(parent);
            }
        }
    }
    return mst;
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
    clock_t begin = clock();
    vector<Edge*> mst = prim();
    clock_t end = clock();
    cout << "Prim's algorithm time: " << double(end - begin) / CLOCKS_PER_SEC << endl;
    cout << "Preorder traversal of tree is \n";
    vector<bool> visited(vertexMap.size(), false);
    vector<int> preorder(vertexMap.size());
    dfs(mst, mst[0]->getOrig(), visited, preorder);
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

// Path: src/GraphAlgorithms.cpp

void Graph::findOdds() {
    for(int i = 0; i < mst_adj.size(); i++){
        if(mst_adj[i].size() % 2 != 0){
            odds.push_back(i);
        }
    }
}

void Graph:: perfectMatching() {
    int closest, minDistance;
    vector<int>::iterator first,itr;
    findOdds();
    while(!odds.empty()){
        first = odds.begin();
        vector<int>::iterator it2 = first + 1;
        vector<int>::iterator it3 = odds.end();
        minDistance = INT_MAX;
        for(; it2 != it3; ++it2){
            if(vertexMap[*first]->getAdj()[*it2]->getWeight() < minDistance){
                minDistance = vertexMap[*first]->getAdj()[*it2]->getWeight();
                closest = *it2;
                itr = first;
            }
        }
        adj[*first].push_back(vertexMap[closest]);
        adj[closest].push_back(vertexMap[*first]);
        odds.erase(itr);
        odds.erase(first);
    }
}
double Graph::findBestPath(int start){
    vector<int> path;
    euler_tour(start,path);
    double length;
    make_hamiltonian(path,length);
    return length;
}
void Graph::euler_tour(int start, vector<int> &path){
    map<int,vector<Vertex*>> temp_list;
    for(int i = 0; i < mst_adj.size(); i++){
        for(int j = 0; j < adj[i].size(); j++){
            temp_list[i][j] = adj[i][j];
        }
    }
    stack<int> stack;
    int pos = start;
    stack.push(pos);
    while(!stack.empty() || temp_list[pos].size() > 0){
        if(temp_list[pos].size() == 0){
            path.push_back(pos);
            pos = stack.top();
            stack.pop();
        }
        else{
            stack.push(pos);
            int next = adj[pos].back()->getId();
            adj[pos].pop_back();
            for(int i = 0; i < adj[next].size(); i++){
                if(adj[next][i]->getId() == pos){
                    adj[next].erase(adj[next].begin() + i);
                    break;
                }
            }
            pos = next;
        }
    }
    path.push_back(pos);
}
void Graph::make_hamiltonian(vector<int> &path, double &length){
    vector<bool> visited(vertexMap.size(),false);
    length = 0;
    int root = path.front();
    vector<int>::iterator itr = path.begin();
    vector<int>::iterator itr2 = path.begin() + 1;
    visited[root] = true;
    while(itr2 != path.end()){
        if(!visited[*itr2]){
            length += vertexMap[*itr]->getAdj()[*itr2]->getWeight();
            itr = itr2;
            visited[*itr2] = true;
            itr2 = itr + 1;
        }
        else{
            itr2 = path.erase(itr2);
        }
    }
    if(itr2 != path.end()){
        length += vertexMap[*itr]->getAdj()[root]->getWeight();
    }
}

void Graph::Christofides(){
    vector<int> path;
    prim();
    perfectMatching();
    double best = INT_MAX;
    int best_index;
    for(int i = 0; i < vertexMap.size(); i++){
        double result = findBestPath(i);
        weights[i] = result;
        if(result < best){
            best = result;
            best_index = i;
        }
    }
    double result = 0.0;
    euler_tour(best_index, path);
    make_hamiltonian(path, result);

    cout << "Best path: " << result << endl;

}