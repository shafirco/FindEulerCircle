#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include "Graph.h"
#include "AdjList.h"
#include <list>
class UndirectedGraph : public Graph {
private:
    AdjList<UndirectedNeighborData>* adjList;
public:
    // Constructor
    UndirectedGraph(int numOfVertex, int numOfEdges);

    // Destructor
    virtual ~UndirectedGraph();

    // Override method to add an edge between two vertices in an undirected manner
    virtual void addEdge(int src, int dest) noexcept(false) override;

    // Override method to check if there is an undirected edge between two vertices
    virtual bool hasEdge(int src, int dest) const override;

    // Override method to check if the graph has an Eulerian circuit
    virtual bool hasEulerianCircuit() const override;

    // Override method to find and print an Eulerian circuit in the graph
    virtual void findAndPrintEulerianCircuit() override;

    // Override method to visit a vertex in the graph
    virtual void visit(int v, int* colors) const noexcept(false) override;

    std::list<int>* findCircuit(int v, AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>** nextArr);

    bool isConnected() const;
    bool isAllDegreesEven() const;
    AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* getNext(AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* u);
    void markEdge(UndirectedNeighborData* u, UndirectedNeighborData* v);
};

#endif // !UNDIRECTED_GRAPH_H
