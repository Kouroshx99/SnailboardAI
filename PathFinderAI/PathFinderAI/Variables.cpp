#include "Variables.h"

Node* startNode;
Vector2 adjacents[] = { Vector2(1, 0), Vector2(-1, 0), Vector2(0, 1), Vector2(0, -1) };

std::vector<Node*> targets5;
std::vector<Node*> targets2;
std::vector<Node*> targets1;
std::vector<Node*> allTargets;