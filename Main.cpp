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

    Graph graph(5);
    graph.genCompleteGraph();

    graph.generatePermutations();
    vector<vector<int>> Cycles1 = graph.findCyclesPermutation(); // SHOULD BE ARROUND 16 CYCLES FOR THE MODEL GRAPH
    cout << "Cycles Permutations: " << Cycles1.size() << endl;
    graph.countCyclesFromTotal();
    graph.printCycleCount();

    cout << endl
         << "It starts here" << endl;

    testGraph.generatePermutations();
    // testGraph.removeSamePaths();
    vector<vector<int>> Cycles = testGraph.findCyclesPermutation(); // SHOULD BE ARROUND 16 CYCLES FOR THE MODEL GRAPH
    cout << "Cycles Permutations: " << Cycles.size() << endl;

    testGraph.countCyclesFromTotal();
    testGraph.printCycleCount();

    return 0;
}