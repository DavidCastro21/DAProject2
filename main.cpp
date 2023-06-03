#include <iostream>
#include <ctime>
#include "src/GraphManager.h"


int main() {
    GraphManager manager;
    Graph graph;

    int input;
    int numProblem;
    int numGraph;
    while(true) {
        cout << "Bem vindo!" << endl << endl;

        cout << "==========================================================================" << endl << endl;

        cout << "1 -> Resolver o TSP recorrendo ao backtracking, num grafo mais pequeno" << endl;
        cout << "2 -> Resolver o TSP recorrendo ao Aproximation Algorithm, num grafo maior" << endl;
        cout << "3 -> Resolver o TSP recorrendo a um algoritmo secreto, num grafo maior" << endl << endl;
        cout << "4 -> Sair" << endl << endl;

        cin >> input;

        cout << "==========================================================================" << endl << endl;

        cout << "Qual é o grafo em que deseja aplicar este algoritmo?" << endl << endl;

        switch (input) {
            case 1: {
                int numProblem = 1;
                cout << "1 -> Grafo shipping" << endl;
                cout << "2 -> Grafo stadiums" << endl;
                cout << "3 -> Grafo tourism" << endl << endl;
                cin >> numGraph;
                manager.readToyGraphs(numGraph);
                graph = manager.getGraph();
                Vertex *initialNode = graph.findVertex(0);
                int number = graph.getNumVertex();
                vector<int> currentPath;
                vector<int> minPath;
                double result = manager.tspBacktracking(initialNode, initialNode, 0, currentPath, minPath, 0.0,
                                                        10000000.0, number);
                cout << result << endl;
                break;
            }
            case 2:
            case 3: {
                cout << "1 -> Grafo com 1000 nós" << endl;
                cout << "2 -> Grafo com 5000 nós" << endl;
                cout << "3 -> Grafo com 10000 nós" << endl << endl;
                cin >> numGraph;
                manager.readRealWorld(numGraph);
                if (input == 2) {
                    manager.triangular();
                }
                else{
                    //do the function of 4.3;
                }
                break;
            }
            default:
                return 0;

        }
        manager.deleteGraph();

    }
}