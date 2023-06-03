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
    /**
     * Complexity: O(1)
     * @brief Default constructor
     */
    Vertex();
    /**
     * Complexity: O(1)
     * @brief Constructor with id
     * @param id - id of the vertex
     */
    Vertex(int id);
    /**
     * Complexity: O(1)
     * @brief Constructor with id and coordinates
     * @param id - id of the vertex
     * @param longitude - longitude of the vertex
     * @param latitude - latitude of the vertex
     */
    Vertex(int id, double longitude, double latitude);
    /**
     * Complexity: O(1)
     * @brief Constructor with id and name
     * @param id - id of the vertex
     * @param name - name of the vertex
     */
    Vertex(int id, string name);

    /**
     * Complexity: O(1)
     * @brief get the id of the vertex
     * @return id of the vertex
     */
    int getId() const;
    /**
     * Complexity: O(1)
     * @brief get the name of the vertex
     * @return name of the vertex
     */
    string getName() const;
    /**
     * Complexity: O(1)
     * @brief get the distance of the vertex
     * @return distance of the vertex
     */
    double getDist() const;
    /**
     * Complexity: O(1)
     * @brief get the latitude of the vertex
     * @return latitude of the vertex
     */
    double getLatitude() const;
    /**
     * Complexity: O(1)
     * @brief get the longitude of the vertex
     * @return longitude of the vertex
     */
    double getLongitude() const;
    /**
     * Complexity: O(1)
     * @brief get the visited of the vertex
     * @return visited of the vertex
     */
    bool isVisited() const;
    /**
     * Complexity: O(1)
     * @brief get the path of the vertex
     * @return path of the vertex
     */
    Edge* getPath() const;
    /**
     * Complexity: O(1)
     * @brief get the adj of the vertex
     * @return adj of the vertex
     */
    vector<Edge*> getAdj() const;
    /**
     * Complexity: O(1)
     * @brief add an edge to the vertex
     * @param dest - destination vertex
     * @param weight - weight of the edge
     */
    void addEdge(Vertex* dest, double weight);
    /**
     * Complexity: O(1)
     * @brief set the id of the vertex
     * @param id - id of the vertex
     */
    void setId(int id);
    /**
     * Complexity: O(1)
     * @brief set the name of the vertex
     * @param name - name of the vertex
     */
    void setName(string name);
    /**
     * Complexity: O(1)
     * @brief set the distance of the vertex
     * @param dist - distance of the vertex
     */
    void setDist(double dist);
    /**
     * Complexity: O(1)
     * @brief set the latitude of the vertex
     * @param lat - latitude of the vertex
     */
    void setLatitude(double lat);
    /**
     * Complexity: O(1)
     * @brief set the longitude of the vertex
     * @param lon - longitude of the vertex
     */
    void setLongitude(double lon);
    /**
     * Complexity: O(1)
     * @brief set the visited of the vertex
     * @param visited - visited of the vertex
     */
    void setVisited(bool visited);
    /**
     * Complexity: O(1)
     * @brief set the path of the vertex
     * @param path - path of the vertex
     */
    void setPath(Edge *path);
    /**
     * Complexity: O(1)
     * @brief operator < of the vertex
     * @param vertex - vertex to compare
     * @return true if the vertex is less than the other
     */
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
    /**
     * Complexity: O(1)
     * @brief Default constructor of the edge
     */
    Edge();
    /**
     * Complexity: O(1)
     * @brief Constructor of the edge with destination
     * @param dest - destination vertex
     */
    Edge(Vertex* dest);
    /**
     * Complexity: O(1)
     * @brief Constructor of the edge with destination and weight
     * @param dest - destination vertex
     * @param weight - weight of the edge
     */
    Edge(Vertex* dest, double weight);
    /**
     * Complexity: O(1)
     * @brief Constructor of the edge with origin, destination and weight
     * @param origin - origin vertex
     * @param dest - destination vertex
     * @param weight - weight of the edge
     */
    Edge(Vertex* origin, Vertex* dest, double weight);

    /**
     * Complexity: O(1)
     * @brief get the destination of the edge
     * @return destination of the edge
     */
    Vertex* getDest() const;
    /**
     * Complexity: O(1)
     * @brief get the weight of the edge
     * @return weight of the edge
     */
    double getWeight() const;
    /**
     * Complexity: O(1)
     * @brief set the destination of the edge
     * @param dest - destination vertex
     */
    void setDest(Vertex* dest);
    /**
     * Complexity: O(1)
     * @brief set the weight of the edge
     * @param weight - weight of the edge
     */
    void setWeight(double weight);
    /**
     * Complexity: O(1)
     * @brief set the origin of the edge
     * @param orig - origin vertex
     */
    void setOrig(Vertex* orig);
    /**
     * Complexity: O(1)
     * @brief get the origin of the edge
     * @return origin of the edge
     */
    Vertex* getOrig() const;
    /**
     * Complexity: O(1)
     * @brief get the reverse of the edge
     * @return reverse of the edge
     */
    Edge* getReverse();
private:
    Vertex* orig;
    Vertex* dest;
    double weight;
};

#endif //UNTITLED1_VERTEXEDGE_H
