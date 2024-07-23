// Snail Board AI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector2.h"
#include <fstream>
#include <sstream>
#include "Graph.h"
#include "Variables.h"
using std::ifstream;
using namespace std;

static bool error = false;

int main()
{
	int** v = new int* [27];

	for (int j = 0; j < 27; ++j) {
		v[j] = new int[27];
	}
	Vector2 startPos;
	Vector2 enemyPos;

	{
		fstream s;
		s.open("input.txt", ios::in);
		string text;

		string lines[31];

		int j = 0;
		while (getline(s, text)) {
			lines[j] = text;
			j++;
		}

		vector<vector<string>> allTokens;

		for (int j = 0;j < 31;j++)
		{
			stringstream is(lines[j]);
			vector<string> tokens;
			string token;

			while (getline(is, token, ' '))
				if (!token.empty())
					tokens.push_back(token);

			allTokens.push_back(tokens);

		}

		startPos = Vector2(stoi(allTokens[0][0]), stoi(allTokens[0][1]));
		enemyPos = Vector2(stoi(allTokens[1][0]), stoi(allTokens[1][1]));

		for (int j = 30; j >= 4; j--)
			for (int i = 0; i < allTokens[j].size(); i++)
			{

				if (stoi(allTokens[j][i]) == -1)
					v[i][j - 4] = 100000;
				if (stoi(allTokens[j][i]) == -2)
					v[i][j - 4] = 8;
				if (stoi(allTokens[j][i]) == 1)
					v[i][j - 4] = e1;
				if (stoi(allTokens[j][i]) == 2)
					v[i][j - 4] = e2;
				if (stoi(allTokens[j][i]) == 5)
					v[i][j - 4] = e5;
				if (stoi(allTokens[j][i]) == 0)
					v[i][j - 4] = ed;

			}

	}

	Graph board = Graph(v, startPos);
	for (int j = 0; j < 27;j++)
		delete[] v[j];
	delete [] v;
	Vector2 targetPos = Vector2(0, 0);

	for (Node* a : targets1)
		allTargets.push_back(a);
	for (Node* a : targets2)
		allTargets.push_back(a);
	for (Node* a : targets5)
		allTargets.push_back(a);

	{

		Vector2 center;
		int cst = 1000000;
		int count = 0;

		center = board.FindCenter().position;
		int golden = 0;

		for (Node* a : allTargets)
		{
			golden = 0;
			golden += a->GetCost();
			golden += (a->position - center).GetMagnitude() * 2.5f;
			golden += 50 * log(0.1 * pow((a->position - startPos).GetMagnitude(), 2));

			golden += (a->position - enemyPos).GetMagnitude();

			switch (a->defaultVal)
			{
			case e5:
			{
				golden -= pow(5, 3);
				break;
			}

			case e2:
			{
				golden -= pow(3, 4);
				break;
			}

			case e1:
			{
				golden -= pow(2, 4);
				break;
			}
			}

			if (golden < cst)
			{
				cst = golden;
				targetPos = a->position;
			}

		}		

	}

	vector<Node*>* n = board.ReturnPath(targetPos);

	Node* far = &board.nodes[0][0];
	float maxDist = -10000;
	for (Node* a : *n)
	{

		if ((a->position - startNode->position).GetMagnitude() > maxDist)
		{

			far = a;
			maxDist = (a->position - startNode->position).GetMagnitude();

		}

	}

	n = board.ReturnPath(far->position);

	Vector2 Right = Vector2(1, 0);
	Vector2 Left = Vector2(-1, 0);
	Vector2 Up = Vector2(0, 1);
	Vector2 Down = Vector2(0, -1);

	if (!error && (*n)[1]->position - (*n)[0]->position == Up)
		cout << "down" << std::endl;
	if (!error && (*n)[1]->position - (*n)[0]->position == Down)
		cout << "up" << std::endl;
	if (!error && (*n)[1]->position - (*n)[0]->position == Right)
		cout << "right" << std::endl;
	if (!error && (*n)[1]->position - (*n)[0]->position == Left)
		cout << "left" << std::endl;
	cout << targetPos.x << " " << targetPos.y << std::endl;
}