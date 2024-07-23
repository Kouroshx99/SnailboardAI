#include "Graph.h"
#include <iostream>
#include "Variables.h"
using namespace std;


Graph::Graph(int** values, Vector2 start)
{

	targets5.clear();
	targets2.clear();
	targets1.clear();

	for (int j = 0; j < Graph::distancesLenght; j++)
		distances[j] = 0;

	for (int j = 0; j < 27; j++)
	{

		for (int i = 0; i < 27; i++)
		{

			nodes[j][i] = Node(Vector2(j, i), values[j][i]);

			if (values[j][i] == e1)
				nodes[j][i].score = 1;
			if (values[j][i] == e2)
				nodes[j][i].score = 2;
			if (values[j][i] == e5)
				nodes[j][i].score = 5;
			if (values[j][i] == ed || values[j][i] == 100000 || values[j][i] == 40)//??
				nodes[j][i].score = 0;

			if (nodes[j][i].defaultVal == e5 ||
				nodes[j][i].defaultVal == e2 ||
				nodes[j][i].defaultVal == e1)
			{

				if (nodes[j][i].defaultVal == e5)
					targets5.push_back(&nodes[j][i]);
				if (nodes[j][i].defaultVal == e2)
					targets2.push_back(&nodes[j][i]);
				if (nodes[j][i].defaultVal == e1)
					targets1.push_back(&nodes[j][i]);

			}

		}

	}


	for (int j = 0; j < 27; j++)
		for (int i = 0; i < 27; i++)
			for (Vector2& a : adjacents)
				if (nodes[j][i].position + a ==
					Vector2::Clamp(nodes[j][i].position + a, Vector2(0, 0), Vector2(27 - 1, 27 - 1)))
				{
					nodes[j][i].edges.push_back(&nodes[j + a.x][i + a.y]);
				}

	nodes[start.x][start.y].SetCost(0);

	startNode = &nodes[start.x][start.y];
	startNode->SetCost(0);

	distances[0] = startNode->GetCost();


	for (Node* neighbour : startNode->edges)
		if (neighbour->UpdateNode(*startNode))
			distances[(neighbour->position.y * 27) + neighbour->position.x] = neighbour->GetCost();

	BellmanFord(distances);

}

void Graph::BellmanFord(int costs[729])
{

	int dist[729];

	for (int j = 0; j < 729; j++)
		dist[j] = 0;

	for (int j = 0; j < 27; j++)
	{
		for (int i = 0; i < 27; i++)
		{

			if (nodes[j][i].predecessor != nullptr)
			{

				dist[nodes[j][i].position.y * 27 + nodes[j][i].position.x] = nodes[j][i].GetCost();

				for (Node* neighbour : nodes[j][i].edges)
				{

					if (nodes[j][i].Critical(&(nodes[j][i]), *neighbour) && neighbour != startNode &&
						neighbour->UpdateNode(nodes[j][i]))
					{
						dist[neighbour->position.y * 27 + neighbour->position.x] =
							neighbour->GetCost();
					}
				}

			}

		}

	}

	bool finished = false;

	for (int j = 0; j < 729; j++)
	{

		if (costs[j] == dist[j])
			finished = true;
		else
		{

			finished = false;
			break;

		}

	}

	if (!finished)
		BellmanFord(dist);

}

std::vector<Node*>* Graph::ReturnPath(Vector2& target)
{

	FindPredecessor(nodes[target.x][target.y]);
	return &path;

}

int Graph::FindPredecessor(Node& pre)
{
	if (&pre == nullptr)
		return 0;
	path.insert(path.begin(), &pre);

	if (&pre == startNode)
	{
		return 0;
	}

	return FindPredecessor(*pre.predecessor);
}

Node& Graph::FindCenter()
{

	for (int j = 0; j < 27; j++)
	{

		for (int i = 0; i < 27; i++)
		{


			nodes[j][i].height += (nodes[j][i].score * 0.1f);

			for (int x = 0; x < 27; x++)
			{

				for (int y = 0; y < 27; y++)
				{

					switch (nodes[j][i].score)
					{

					case 5:
					{
						if (j != x || i != (y))
							nodes[x][y].height += ((1 / (Vector2(j, i) - Vector2(x, y)).GetMagnitude()) * 0.5f);
						break;
					}
					case 2:
					{
						if (j != x || i != (y))
							nodes[x][y].height += ((1 / (Vector2(j, i) - Vector2(x, y)).GetMagnitude()) * 0.2f);
						break;
					}
					case 1:
					{
						if (j != x || i != (y))
							nodes[x][y].height += ((1 / (Vector2(j, i) - Vector2(x, y)).GetMagnitude()) * 0.1f);
						break;
					}

					}

				}

			}

		}

	}

	vector<Node> node;
	startNode->height = 0;

	for (int j = 0; j < 27; j++)
	{

		for (int i = 0; i < 27; i++)
		{

			if (nodes[j][i].score != 0)
			{

				if (node.size() != 0)
				{
					for (int t = 0; t < node.size(); t++)
					{

						if (nodes[j][i].height > node[t].height)
						{

							node.insert(node.begin() + t, nodes[j][i]);

							if (node.size() > 2)
							{
								node.pop_back();
							}

						}

					}

				}
				else
					node.push_back(nodes[j][i]);

			}

		}

	}

	Node hh = Node();
	Vector2 distance = Vector2(1000, 1000);

	for (int j = 0; j < node.size(); j++)
	{

		if ((node[j].position - startNode->position).GetMagnitude() < distance.GetMagnitude())
		{

			hh = node[j];
			distance = (node[j].position - startNode->position);

		}

	}

	return hh;

}