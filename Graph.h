#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include "InvalidInputException.h"
enum colors {WHITE, GRAY, BLACK};

class Graph {
protected:
    int numOfVertex;
    int numOfEdges;
public:
    Graph(int n, int m) noexcept(false) : numOfVertex(n), numOfEdges(m) { if (n <= 0 || m <= 0) throw InvalidInputException();}
    // Destructor
    virtual ~Graph() {}

    // Abstract method to add an edge between two vertices
    virtual void addEdge(int src, int dest) noexcept(false) = 0;

    // Abstract method to check if there is an edge between two vertices
    virtual bool hasEdge(int src, int dest) const = 0;

    // Abstract method to check if the graph has an Eulerian circuit
    virtual bool hasEulerianCircuit() const = 0;

    // Abstract method to find and print an Eulerian circuit in the graph
    virtual void findAndPrintEulerianCircuit() = 0;

    // Abstract method to visit a vertex in the graph
    virtual void visit(int v, int* colors) const noexcept(false) = 0;


    bool isValidVertex(int v) const;
    void printPath(std::list<int> path) const;


};
#endif // !GRAPH_H