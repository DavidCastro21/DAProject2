#include <iostream>
#include "src/ReadFiles.h"


int main() {
    ReadFiles readfiles1 = ReadFiles();
    readfiles1.readRealWorld(1);
    Graph graph = readfiles1.getGraph();
    for(auto i : graph.getVertexSet()){
        cout << i->id <<endl<< i->latitude<<endl << i->longitude << endl;
    }
    return 0;
}
