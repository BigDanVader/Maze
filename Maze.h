/*
Class: Maze
Author: Dan Luoma
Description: Header for the Maze class. See Maze.cpp for description
*/
#ifndef MAZE_H
#define MAZE_H

#include<iostream>
#include"DoublyLinkedList.h"

class Maze
{
public:
	//constructors
	Maze();
	Maze(int size, int obs);

	//mutators
	void makeMaze(int size, int obs);
	void runMaze();

	//accessor
	bool getEnd();

private:
	//private data members
	DoublyLinkedList<int> *path;
	char **maze;
	bool **visited;
	int mazeSize;
	bool end;

	//private mutators
	void fillMaze();
	void fillObs(int obs);
	void findPath(int x, int y);

	//private accessors
	void animation();
	bool isClear(int row, int col);
	void printMaze();
};
#endif
