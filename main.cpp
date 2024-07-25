#include "UndirectedGraph.h"
#include "DirectedGraph.h"
#include <iostream>
using namespace std;

int main() {
    char directed;
    int numVertices, numEdges;
    Graph* graph;
    std::cout << "Is the graph directed: y/n"<<endl;
    std::cin >> directed;
    if (directed != 'y' && directed != 'n') {
        cout << InvalidInputException().Message();
        return 0;
    }
    std::cin >> numVertices;
    std::cin >> numEdges;
    try {
        if (directed == 'y') {
            graph = new DirectedGraph(numVertices, numEdges);
        }
        else {
            graph = new UndirectedGraph(numVertices, numEdges);
        }
        int u, v;
        for (int i = 0; i < numEdges; i++) {
            std::cin >> u >> v;
            graph->addEdge(u, v);
        }
        if (!graph->hasEulerianCircuit())
            cout << "The graph is not aulerian" << endl;
        else {
            cout << "The graph is aulerian" << endl;
            graph->findAndPrintEulerianCircuit();
        }
        // Clean up memory
        delete graph;
    }
    catch (InvalidInputException e) {
        cout << e.Message();
    }
    return 0;
}