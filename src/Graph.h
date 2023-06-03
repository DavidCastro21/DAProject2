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
#include <unordered_set>
#include <stack>
#include <map>
#include "VertexEdge.h"
#include <cmath>


using namespace std;

class Graph {
public:
    /**
     * Complexity: O(1)
     * Default constructor
     * Initializes an empty graph
     */
    Graph();
    /**
     * Complexity: O(1)
     * Constructor
     * Initializes a graph with a given number of vertices
     */
    explicit Graph(int nrVertex);
    /**
     * Complexity: O(1)
     * Adds a vertex to the graph with a given id
     * @param id - id of the vertex
     * @return true if the vertex was added, false otherwise
     */
    bool addVertex(const int &id);
    /**
     * Complexity: O(1)
     * Adds a vertex to the graph with a given id and coordinates
     * @param id - id of the vertex
     * @param longitude - longitude of the vertex
     * @param latitude - latitude of the vertex
     * @return true if the vertex was added, false otherwise
     */
    bool addVertex(const int &id, double longitude, double latitude);
    /**
     * Complexity: O(1)
     * Adds a vertex to the graph with a given id and name
     * @param id - id of the vertex
     * @param name - name of the vertex
     * @return true if the vertex was added, false otherwise
     */
    bool addVertex(const int &id, string name);
    /**
     * Complexity: O(1)
     * Adds an edge to the graph with a given source, destination and weight
     * @param sourc - id of the source vertex
     * @param dest - id of the destination vertex
     * @param w - weight of the edge
     * @return true if the edge was added, false otherwise
     */
    bool addEdge(const int &sourc, const int &dest, double w) const;
    /**
     * Complexity: O(1)
     * Removes a vertex from the graph with a given id
     * @param id - id of the vertex
     * @return true if the vertex was removed, false otherwise
     */
    bool removeVertex(const int &id);

    /**
     * Complexity: O(1)
     * Gets the number of vertices in the graph
     * @return the number of vertices in the graph
     */
    int getNumVertex() const;
    /**
     * Complexity: O(1)
     * Gets the vertex map of the graph
     * @return the vertex map of the graph
     */
    const unordered_map<int, Vertex *> getVertexMap() const;

    /**
     * Complexity: O(1)
     * Gets the vertex with a given id
     * @param id - id of the vertex
     * @return the vertex with the given id
     */
    Vertex * findVertex(const int &id) const;
    // int findVertexIdx(const int &id) const;

    /**
     * Complexity: O(V + E)
     * @brief Calculates the distance of the path by using the triangular inequality
     * @return The distance of the path
     */
    double triangularApproximation();
    /**
     * Complexity: O(V + E)
     * @brief DFS algorithm to order the minimum spanning tree
     * @param mst - vector of edges that form the minimum spanning tree
     * @param v - vertex to start the DFS
     * @param visited - vector of visited vertices
     * @param path - vector of vertices in the order of the DFS
     */
    void dfs(unordered_map<Vertex*,vector<Edge*>>& mst, Vertex* v, vector<bool> &visited, vector<int> &path);
    /**
     * Complexity: O((E+V) log V)
     * @brief Prim algorithm to find the minimum spanning tree
     * @return vector of edges that form the minimum spanning tree
     */
    unordered_map<Vertex*,vector<Edge*>> prim();
    /**
     * Complexity: O(1)
     * @brief calculates the distance between two nodes using the haversine formula
     * @param initialNode - the node from which the distance is calculated
     * @param finalNode - the node to which the distance is calculated
     * @return the distance between the two nodes
     */
    double haversine(Vertex *initialNode, Vertex *finalNode);
    /**
     * Complexity: O(n), n is the average number of edges per vertex
     * @param id1 - id of the origin vertex
     * @param id2 - id of the destination vertex
     * @return true if there is a edge between the two vertices, false otherwise
     */
    bool haveEdge(int id1, int id2);
    /**
     * Complexity: O(P), P is the path size
     * @brief returns the distance of a path, considering the edges and the haversine distance
     * @param path - the path to calculate the distance
     * @return the distance of the path
     */
    double getDistance(const vector<int>& path);
    /**
     * Complexity: O(V^2)
     * @brief Calculates the distance of the path by using the nearest neighbor algorithm
     * @param initialNode - the initial node
     * @param currentNode - the current node
     * @param path - the path
     * @param graphSize - the size of the graph
     * @param distance - the distance of the path
     * @param allVisited - boolean that indicates if all nodes were visited
     * @return The distance of the path
     */
    double nearestNeighbor(Vertex* &initialNode, Vertex* &currentNode, vector<Edge*> &path, int &graphSize, double &distance, bool allVisited = false);
    /**
     * Complexity: O(V)
     * @brief Calculates the distance of the path by using the nearest neighbor algorithm
     * @param vertexMap - the map of the vertices
     * @return The count of nodes already visited
     */
    int nrNodesAlreadyVisited(unordered_map<int, Vertex*> vertexMap);
    /**
     * Complexity: O(1)
     * @brief deletes the vertex map
     */
    void deleteVertexMap();
    /**
     * Complexity: O(1)
     * @brief deletes the vertex set
     */
    void deleteVertexSet();
protected:
    int numVertex;
    unordered_map<int,Vertex*> vertexMap;
    vector<Vertex*> vertexSet;
    map<int, vector<Vertex*>> mst_adj;
    vector<int> odds;
    map<int, vector<Vertex*>> adj;
    map<int, double> weights;
};
/**
 * @brief Class that compares the weight of two edges
 */
class WeightCompare{
    public:
        bool operator()(const Vertex* e1, const Vertex * e2) const{
            return e1->getDist() > e2->getDist();
    }
};



#endif /* DA_TP_CLASSES_GRAPH */