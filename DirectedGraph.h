#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H


#include "Graph.h"
#include "AdjList.h"
#include <list>
class DirectedGraph : public Graph {
private:
    AdjList<DirectedNighborData>* adjList;
public:
    // Constructor
    DirectedGraph(int numOfVertex, int numOfEdges);

    // Destructor
    virtual ~DirectedGraph();

    // Override method to add an edge between two vertices in a directed manner
    virtual void addEdge(int src, int dest) noexcept(false) override;

    // Override method to check if there is a directed edge between two vertices
    virtual bool hasEdge(int src, int dest) const override;

    // Override method to check if the graph has an Eulerian circuit
    virtual bool hasEulerianCircuit() const override;

    // Override method to find and print an Eulerian circuit in the graph
    virtual void findAndPrintEulerianCircuit() override;

    // visit algorithm by the dfs algorithm
    virtual void visit(int v, int* colors) const noexcept(false) override;

    std::list<int>* findCircuit(int v, AdjList<DirectedNighborData>::Node<DirectedNighborData>** nextArr);

    bool isOutInDegreesEquals() const;

    bool isStronglyConnected() const;

    int getInDegree(int v) const;
    int getOutDegree(int v) const;

    DirectedGraph* getTransposeGraph() const;
};

#endif // !DIRECTED_GRAPH_H