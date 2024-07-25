#include "UndirectedGraph.h"
#include <iostream>

using namespace std;
UndirectedGraph::UndirectedGraph(int numOfVertex, int numOfEdges) : Graph(numOfVertex, numOfEdges) {
	adjList = new AdjList<UndirectedNeighborData>[numOfVertex];
}

UndirectedGraph::~UndirectedGraph() {
	delete[] adjList;
}

bool UndirectedGraph::hasEdge(int u, int v)const {
	for (AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* p = adjList[u - 1].head; p != nullptr;
		p = p->next) {
		if (p->data.id == v)
			return true;
	}
	return false;
}


void UndirectedGraph::addEdge(int u, int v) {
	if (hasEdge(u, v) || !isValidVertex(u) || !isValidVertex(v))
		throw InvalidInputException();
	adjList[u - 1].append({ v, nullptr }); // init each neighbor with null as twin.
	adjList[v - 1].append({ u, nullptr });
	adjList[u - 1].getTail().twin = &adjList[v-1].getTail(); // set twins to repesents undirected edge.
	adjList[v - 1].getTail().twin = &adjList[u-1].getTail();
}

bool UndirectedGraph::hasEulerianCircuit() const {
	return (isConnected() && isAllDegreesEven());
}

bool UndirectedGraph::isAllDegreesEven() const {
	for (int i = 0; i < numOfVertex; i++)
		if (adjList[i].getSize() % 2 == 1)
			return false;
	return true;
}

bool UndirectedGraph::isConnected() const {
	int* colors = new int[numOfVertex];
	bool res = true;
	for (int i = 0; i < numOfVertex; i++)
		colors[i] = WHITE;

	visit(1, colors);

	for (int i = 0; i < numOfVertex; i++)
		if (colors[i] != BLACK)
			res = false; // which means one of the edges have not been visited..
	delete[] colors;
	return res;

}

// visit recursive algorithm from dfs algorithm.
void UndirectedGraph::visit(int v, int* colors) const {
	colors[v - 1] = GRAY;
	AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* p = adjList[v - 1].head;

	while (p != nullptr)
	{
		if (colors[p->data.id - 1] == WHITE)
			visit(p->data.id, colors);
		p = p->next;
	}
	colors[v - 1] = BLACK;
}

void UndirectedGraph::findAndPrintEulerianCircuit() {
	if (!hasEulerianCircuit())
	{
		cout << "No euler circle"<<endl;
		return;
	}
		
	AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>** nextArr = 
		new AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>*[numOfVertex];

	int curr;

	list<int> circle, *temp;
	list<int>::iterator itr, tempItr;
	for (int i = 0; i < numOfVertex; i++)
		nextArr[i] = adjList[i].head;

	temp = findCircuit(1, nextArr);
	circle.insert(circle.begin(), temp->begin(), temp->end()); //init first circle in the graph (which obviesly exist).
	delete temp;
	itr = circle.begin();
	// loop through each vertex in circle until all edges have been passed.
	while (itr != circle.end())
	{
		curr = *itr;
		if (nextArr[curr - 1] == nullptr)
			++itr;
		else
		{
			temp = findCircuit(curr, nextArr);
			tempItr = itr;
			++tempItr;
			circle.insert(tempItr, ++temp->begin(), temp->end()); // paste the found circle.
			delete temp;
			if(nextArr[curr-1] != nullptr)
				nextArr[curr - 1] = nextArr[curr - 1]->next;
		}
	}
	delete[] nextArr;
	printPath(circle);
}

std::list<int>* UndirectedGraph::findCircuit(int v, 
	AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>** nextArr)
{
	list<int>* res = new list<int>;
	int curr = v, u;
	res->push_back(v);
	while (nextArr[curr - 1] != nullptr)
	{
		u = nextArr[curr - 1]->data.id;
		res->push_back(u);
		markEdge(&nextArr[curr - 1]->data, nextArr[curr - 1]->data.twin);
		nextArr[curr - 1] = getNext(nextArr[curr - 1]);
		nextArr[u - 1] = getNext(nextArr[u - 1]);
		curr = u;
	}
	return res;
}

AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* UndirectedGraph::getNext(AdjList<UndirectedNeighborData>::Node<UndirectedNeighborData>* u)
{
	while (u != nullptr)
	{
		if (u->data.mark)
			u = u->next;
		else
			return u;
	}
	return u;
}

void UndirectedGraph::markEdge(UndirectedNeighborData* u, UndirectedNeighborData* v)
{
	u->mark = true;
	v->mark = true;
}

