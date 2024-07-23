#include "Node.h"
#include "Graph.h"
#include "Variables.h"
#include <iostream>


const int* Node::GetDefaultValue(Node& a)
{

    if (&a == startNode)
        return &defaultVal;
    if (this == &a)
        return &ed;
    else
        return GetDefaultValue(*a.predecessor);
}

Node::Node(Vector2 pos, int val)
{

    requestingNode = nullptr;
    position = pos;
    defaultVal = val;

}

bool Node::UpdateNode(Node& pre)
{

    requestingNode = &pre;
    int value = *GetDefaultValue(*requestingNode);

    if (cost > pre.cost + value)
    {

        predecessor = &pre;
        requestingNode = &pre;
        this->SetCost(pre.cost + value);
        return true;

    }
    else
        return false;

}

bool Node::Critical(Node* a, Node& ref)
{
    if (a == startNode)
        return true;
    else
    {

        if (a == &ref)
            return false;
        else
            return this->Critical(a->predecessor, ref);

    }
}

int Node::GetCost()
{
    return cost;
}
void Node::SetCost(int cost)
{
    this->cost = cost;
}
