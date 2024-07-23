#pragma once
#include "Vector2.h"
#include <climits>
#include <vector>

class Node
{

private:
	Node* requestingNode = nullptr;

	const int* GetDefaultValue(Node& a);
	int cost = INT_MAX / 200;

public:
	Vector2 position;
	int score = 0;
	int defaultVal;
	Node* predecessor = nullptr;
	float height = 0;
	std::vector<Node*> edges;

	Node() = default;
	Node(Vector2 pos, int val);

	bool UpdateNode(Node& pre);
	bool Critical(Node* a, Node& ref);
	int GetCost();
    void SetCost(int cost);

};