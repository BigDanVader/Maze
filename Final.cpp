/*
Test File
Author: Dan Luoma
Description: Used to test the Maze class
*/
#include "stdafx.h"
#include <iostream>
#include "Maze.h"

using std::cout;
using std::endl;
using std::cin;

int main()
{
	Maze m;
	
	cout << "Enter how big you wish the sides of the maze to be: " << endl;
	int size;
	cin >> size;
	cout << "Enter how many obstacles you wish to put in the maze." << endl;
	cout << "WARNING: A large number of obstacles may prevent maze from being solved: " << endl;
	int obstacles;
	cin >> obstacles;

	m.makeMaze(size, obstacles);
	m.runMaze();

	if (m.getEnd())
	{
		cout << "Winner! The rat found the end of the maze successfully." << endl;
	}
	else
	{
		cout << "No winner! Obstacles prevented the rat from reaching the end of the maze." << endl;
	}
    return 0;
}

