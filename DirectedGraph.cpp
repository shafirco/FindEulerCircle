#include "DirectedGraph.h"
#include <iostream>
#include <list>
using namespace std;

DirectedGraph::DirectedGraph(int numOfVertex, int numOfEdges) : Graph(numOfVertex, numOfEdges) {
	adjList = new AdjList<DirectedNighborData>[numOfVertex];
}

// Destructor
DirectedGraph::~DirectedGraph() {
	delete[] adjList;
}



// Override method to add an edge between two vertices in a directed manner
void DirectedGraph::addEdge(int src, int dest) noexcept(false) {
	if (hasEdge(src, dest) || !isValidVertex(src) || !isValidVertex(src))
		throw InvalidInputException();
	adjList[src - 1].append(dest);
}

 /*Override method to check if there is a directed edge between two vertices*/
bool DirectedGraph::hasEdge(int src, int dest) const {
	for (AdjList<DirectedNighborData>::Node<DirectedNighborData>* p = adjList[src - 1].head; p != nullptr;
		p = p->next) {
		if (p->data == dest)
			return true;
	}
	return false;
}

// Override method to check if the graph has an Eulerian circuit
bool DirectedGraph::hasEulerianCircuit() const {
	return (isOutInDegreesEquals() && isStronglyConnected());
}

// a function to make the transpose graph.
DirectedGraph* DirectedGraph::getTransposeGraph() const{
	DirectedGraph* transposeGraph = new DirectedGraph(numOfVertex, numOfEdges);
	for (int i = 0; i < numOfVertex; i++) {
		for (AdjList<DirectedNighborData>::Node<DirectedNighborData>* p = adjList[i].head; p != nullptr;
			p = p->next) {
			transposeGraph->addEdge(p->data, i + 1);
		}
	}
	return transposeGraph;
}

// checks if the graph is strongly connected, using the dfs visit algorithm.
bool DirectedGraph::isStronglyConnected() const{
	int* colors = new int[numOfVertex];
	bool res = true;
	for (int i = 0; i < numOfVertex; i++)
		colors[i] = WHITE;
	visit(1, colors);
	for (int i = 0; i < numOfVertex; i++)
		if (colors[i] != BLACK)
			res = false;
	if (!res) { //which means one of the vertices have not been visited.
		delete[] colors;
		return res;
	}
	for (int i = 0; i < numOfVertex; i++)
		colors[i] = WHITE;

	DirectedGraph* transposeGraph = getTransposeGraph();

	transposeGraph->visit(1, colors); // visit the transpose graph.
	for (int i = 0; i < numOfVertex; i++)
		if (colors[i] != BLACK)
			res = false;
	delete[] colors;
	delete transposeGraph;
	return res;
}

bool DirectedGraph::isOutInDegreesEquals() const{
	for (int i = 1; i <= numOfVertex; i++)
		if (getOutDegree(i) != getInDegree(i))
			return false;
	return true;

}

int DirectedGraph::getInDegree(int v) const{
	int count = 0;
	//loops throw each adjList, and checks if v in it. if so, increments count by 1.
	for (int i = 0; i < numOfVertex; i++) {
		for (AdjList<DirectedNighborData>::Node<DirectedNighborData>* p = adjList[i].head; p != nullptr; 
			p=p->next) {
			if (p->data == v)
				count++;
		}
	}
	return count;
}
int DirectedGraph::getOutDegree(int v) const{
	return adjList[v - 1].getSize();
}

// Override method to find and print an Eulerian circuit in the graph
void DirectedGraph::findAndPrintEulerianCircuit() {

	AdjList<DirectedNighborData>::Node<DirectedNighborData>** nextArr =
		new AdjList<DirectedNighborData>::Node<DirectedNighborData>*[numOfVertex];

	int curr;

	list<int> circle, * temp;
	list<int>::iterator itr, tempItr;
	for (int i = 0; i < numOfVertex; i++)
		nextArr[i] = adjList[i].head;

	temp = findCircuit(1, nextArr);
	circle.insert(circle.begin(), temp->begin(), temp->end());
	delete temp;
	itr = circle.begin();
	// loop through the given circle, until all edges have been passed.
	while (itr != circle.end()) 
	{
		curr = *itr;
		if (nextArr[curr - 1] == nullptr)
			++itr;
		else
		{
			temp = findCircuit(curr, nextArr);
			tempItr = itr;
			++tempItr; // to save the location in the list.
			circle.insert(tempItr, ++temp->begin(), temp->end());
			delete temp;
			if (nextArr[curr - 1] != nullptr)
				nextArr[curr - 1] = nextArr[curr - 1]->next;
		}
	}
	delete[] nextArr;
	printPath(circle);
}

list<int>* DirectedGraph::findCircuit(int v, 
	AdjList<DirectedNighborData>::Node<DirectedNighborData>** nextArr)
{
	list<int>* res = new list<int>;
	int curr = v, u;
	res->push_back(v);
	while (nextArr[curr - 1] != nullptr)
	{
		u = nextArr[curr - 1]->data;
		res->push_back(u);
		nextArr[curr - 1] = nextArr[curr - 1]->next;
		curr = u;
	}
	return res;
}


void DirectedGraph::visit(int v, int* colors) const noexcept(false) {

	if (!isValidVertex(v))
		throw InvalidInputException();
	colors[v - 1] = GRAY;
	AdjList<DirectedNighborData>::Node<DirectedNighborData>* p = adjList[v - 1].head;

	while (p != nullptr)
	{
		if (colors[p->data - 1] == WHITE)
			visit(p->data, colors);
		p = p->next;
	}
	colors[v - 1] = BLACK;
}
