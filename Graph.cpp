#include "Graph.h"
#include <list>
#include <iostream>

using namespace std;
void Graph::printPath(list<int> path) const {
	list<int>::iterator itr = path.begin();
	cout << "(";
	while (itr != path.end())
	{
		cout << *itr;
		if (++itr != path.end())
			cout << ",";
	}
	cout << ")" << endl;
}


bool Graph::isValidVertex(int v)const {
	return (v > 0 && v <= numOfVertex);
}