#include <iostream>
#include "src/ReadFiles.h"


int main() {
    ReadFiles readfiles1 = ReadFiles();
    readfiles1.readRealWorld(3);
    Graph graph = readfiles1.getGraph();
    return 0;
}

