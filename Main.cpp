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
    testGraph.setStorePaths(true); // Necessario para manter o codigo "memory safe", caso esteja setado para TRUE, ira armazenar todos os caminhos possiveis
                                   // oque pode gerar um consumo de memoria muito alto para grafos grandes(>9 vertices), para grafos pequenos(<=9 vertices) é seguro
                                   // porem o valor ver como FALSE por padrao por ser mais seguro e levemente +eficiente.
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
    testGraph.PERMPrintCyclePathCount();
    testGraph.PERMPrintUniqueCyclesCount();
    testGraph.PERMPrintPaths();
    testGraph.DFSPrintCyclePathCount();
    testGraph.DFSPrintUniqueCyclesCount();
    testGraph.DFSPrintPaths();

    cout << "Array of Graphs" << endl;
    const int size = 10;
    Graph graphs[size];

    for (int i = 0; i < size; i++)
    {
        graphs[i] = Graph(i + 1);
        cout << "Graph " << i + 1 << endl;

        graphs[i].genCompleteGraph();
        graphs[i].PERMPrintCyclePathCount();
        // graphs[i].PERMPrintUniqueCyclesCount();
        graphs[i].DFSPrintCyclePathCount();
        // graphs[i].DFSPrintUniqueCyclesCount();
        cout << endl;
    }
    // graphs[5].PERMPrintPaths();

    return 0;
}