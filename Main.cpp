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
    // Graph testGraph(6);
    // testGraph.addEdge(0, 1);
    // testGraph.addEdge(0, 3);
    // testGraph.addEdge(0, 4);
    // testGraph.addEdge(1, 2);
    // testGraph.addEdge(1, 3);
    // testGraph.addEdge(1, 4);
    // testGraph.addEdge(2, 3);
    // testGraph.addEdge(2, 4);
    // testGraph.addEdge(2, 5);
    // testGraph.addEdge(3, 5);
    // testGraph.addEdge(4, 5);
    // testGraph.printGraph();
    // testGraph.generatePermutations();

    cout << "Array of Graphs" << endl;
    const int size = 10;
    Graph graphs[size];

    for (int i = 0; i < size; i++) {
        graphs[i] = Graph(i + 1);
        cout << "Graph " << i + 1 << endl;

        graphs[i].genCompleteGraph();
        graphs[i].PERMPrintCyclePathCount();
        // graphs[i].PERMPrintUniqueCyclesCount();
        graphs[i].DFSPrintCyclePathCount();
        // graphs[i].DFSPrintUniqueCyclesCount();
        cout << endl;
    }

    return 0;
}