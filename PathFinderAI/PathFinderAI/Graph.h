#pragma once
#include "Node.h"
using namespace std;

class Graph
{

private:

	static const int distancesLenght = 27 * 27;
	int distances[distancesLenght];

public:

	Node nodes[27][27];

	vector<Node*> path;

	Graph(int** values, Vector2 start);

	void BellmanFord(int costs[729]);

	std::vector<Node*>* ReturnPath(Vector2& target);
	int FindPredecessor(Node& pre);

	Node& FindCenter();

};