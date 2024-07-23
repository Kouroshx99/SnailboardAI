#pragma once
#include <vector>
#include "Node.h"

const int ed = 1;
const int e1 = -1;
const int e2 = -4;
const int e5 = -8;

extern Node* startNode;
extern Vector2 adjacents[4];

extern std::vector<Node*> targets5;
extern std::vector<Node*> targets2;
extern std::vector<Node*> targets1;
extern std::vector<Node*> allTargets;