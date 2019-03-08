/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			labirinth[i][j] = values[i][j];
		}
	this->initializeVisited();
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{

	if(labirinth[y][x] == 2) {
		cout << "Solution at x: " << x << " y: " << y << endl;
		return true;
	}
	if(labirinth[y][x] == 0 || visited[y][x]) {
		return false;
	}
	visited[y][x] = true;
	if(labirinth[y][x] == 1) {
		if (findGoal(x + 1, y)) return true;
		else if (findGoal(x, y + 1)) return true;
		else if (findGoal(x - 1, y)) return true;
		else return (findGoal(x, y + 1));

	}
	return false;
}


