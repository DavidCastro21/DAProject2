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
        cout << "2 -> Resolver o TSP recorrendo ao Aproximation Algorithm, num grafo grande" << endl;
        cout << "3 -> Resolver o TSP recorrendo ao Nearest Neighbour Algorithm , num grafo qualquer completo" << endl << endl;
        cout << "4 -> Sair" << endl << endl;

        cin >> input;
        if(input==1 || input==2 || input==3) {

            cout << "==========================================================================" << endl << endl;

            cout << "Qual é o grafo em que deseja aplicar este algoritmo?" << endl << endl;
        }

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
                int size = graph.getNumVertex();
                clock_t start = clock();
                double result = manager.tspBacktracking(initialNode, initialNode, 0, currentPath, minPath, 0.0,10000000.0, number);
                cout << result << endl;
                clock_t end = clock();
                double duration = double(end - start) / CLOCKS_PER_SEC * 1000.0;
                cout << "Time taken: " << duration << " milliseconds." << endl;
                cout << "-----------------------" << endl;
                break;
            }
            case 2:{
                cout << "1 -> Grafo com 1000 nós" << endl;
                cout << "2 -> Grafo com 5000 nós" << endl;
                cout << "3 -> Grafo com 10000 nós" << endl;
                cin >> numGraph;
                manager.readRealWorld(numGraph);
                manager.triangular();
                break;
            }
            case 3: {
                cout << "1 -> Grafo stadiums" << endl;
                cout << "2 -> Grafo tourism" << endl;

                cout << "3 -> Grafo com 25 nós" << endl;
                cout << "4 -> Grafo com 50 nós" << endl;
                cout << "5 -> Grafo com 75 nós" << endl;
                cout << "6 -> Grafo com 100 nós" << endl;
                cout << "7 -> Grafo com 200 nós" << endl;
                cout << "8 -> Grafo com 300 nós" << endl;
                cout << "9 -> Grafo com 400 nós" << endl;
                cout << "10 -> Grafo com 500 nós" << endl;
                cout << "11 -> Grafo com 600 nós" << endl;
                cout << "12 -> Grafo com 700 nós" << endl;
                cout << "13 -> Grafo com 800 nós" << endl;
                cout << "14 -> Grafo com 900 nós" << endl;

                cout << "15 -> Grafo com 1000 nós" << endl;

                cin >> numGraph;

                switch (numGraph) {
                    case 1:
                    case 2:
                        manager.readToyGraphs(numGraph + 1);
                        break;
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                    case 14:
                        manager.readExtraFully(numGraph - 2);
                        break;
                    case 15:
                        manager.readRealWorld(1);
                        break;
                    default:
                        cout << "Invalid Input; Terminating program" << endl;
                        return 0;
                }
                graph = manager.getGraph();
                int size = graph.getNumVertex();
                double result2 = manager.heuristic(size);
                cout << result2 << endl;
                break;
            }
            default:
                return 0;
        }
        manager.deleteGraph();

    }
}