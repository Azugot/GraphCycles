#include <iostream>
#include "Graph.hpp"
#include <vector>

using namespace std;
int main(int argc, char const *argv[])
{
    // a0 -134
    // b1 -0234
    // c2 -1345
    // d3 -0125
    // e4 -0125
    // f5 -234
    Graph testGraph(6);
    testGraph.addEdge(0, 1);
    testGraph.addEdge(0, 3);
    testGraph.addEdge(0, 4);
    testGraph.addEdge(1, 2);
    testGraph.addEdge(1, 3);
    testGraph.addEdge(1, 4);
    testGraph.addEdge(2, 3);
    testGraph.addEdge(2, 4);
    testGraph.addEdge(2, 5);
    testGraph.addEdge(3, 5);
    testGraph.addEdge(4, 5);
    testGraph.printGraph();
    testGraph.generatePermutations();

    testGraph.PERMPrintCyclePathCount();
    testGraph.PERMPrintUniqueCyclesCount(); //Possivelmente quebrado, estou sem energias para fazer o debugging, e o do DFS parece estar correto ent fds

    //testGraph.PERMPrintPaths();

    testGraph.DFSPrintCyclePathCount();
    testGraph.DFSPrintUniqueCyclesCount();

    testGraph.DFSPrintPaths();

    cout << endl
         << "It starts here" << endl;

    Graph graph(5);
    graph.genCompleteGraph();
    graph.PERMPrintCyclePathCount();
    graph.PERMPrintUniqueCyclesCount();

    graph.DFSPrintCyclePathCount();
    graph.DFSPrintUniqueCyclesCount();

    return 0;
}