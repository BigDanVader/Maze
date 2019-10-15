/*
Class: Maze
Author: Dan Luoma
Description: A class that simulates a rat trying to find the exit of a maze
*/
#include "stdafx.h"
#include <chrono>
#include <time.h>
#include <thread>
#include "Maze.h"

using std::cout;
using std::endl;

/*
Function: Maze()
Author: Dan Luoma
Description: Standard constructor
*/
Maze::Maze()
{
}

/*
Function: Maze(int size, int obs)
Author: Dan Luoma
Description: Constructor that calls makeMaze and passes @param size and @param obs
Inputs:Two ints
*/
Maze::Maze(int size, int obs)
{
	this->makeMaze(size, obs);
}

/*
Function: makeMaze(int size, int obs)
Author: Dan Luoma
Description: Initilizes the private data members of the class, then calls fillMaze and fillObs
Inputs: Two ints
*/
void Maze::makeMaze(int size, int obs)
{
	this->mazeSize = size + 1;
	this->path = new DoublyLinkedList<int>;

	this->maze = new char*[this->mazeSize];
	for (int i = 0; i < this->mazeSize; i++)
		this->maze[i] = new char[this->mazeSize];

	this->visited = new bool*[this->mazeSize];
	for (int i = 0; i < this->mazeSize; i++)
		visited[i] = new bool[this->mazeSize];

	for (int i = 0; i < this->mazeSize; i++)
		for (int j = 0; j < this->mazeSize; j++)
			this->visited[i][j] = false;

	this->fillMaze();
	this->fillObs(obs);
}

/*
Function: runMaze()
Author: Dan Luoma
Description: Calls the findPath private member function and passes it an initial coordinate of 1, 1
*/
void Maze::runMaze()
{
	this->findPath(1, 1);
}

/*
Function: getEnd()
Author: Dan Luoma
Description: Returns the value stored in @param end.
Output: A bool
*/
bool Maze::getEnd()
{
	return this->end;
}

/*
Function: fillMaze()
Author: Dan Luoma
Description: Fills @param maze with side length @param mazeSize with 0's, then fills the border with 1's to keep the "rat" in bounds.
*/
void Maze::fillMaze()
{
	for (int i = 0; i < this->mazeSize; i++)
		for (int j = 0; j < this->mazeSize; j++)
			this->maze[i][j] = '0';

	for (int i = 0; i < this->mazeSize; i++)
	{
		this->maze[0][i] = this->maze[this->mazeSize - 1][i] = '1';
		this->maze[i][0] = this->maze[i][this->mazeSize - 1] = '1';
	}
}

/*
Function: fillObs(int obs)
Author: Dan Luoma
Description: Fills @param maze with randomly placed 1's to act as obstacles. Also places the maze exit.
Inputs: An int
*/
void Maze::fillObs(int obs)
{
	srand(time(NULL));

	for (int i = 1; i <= obs; i++)
	{
		//produces random numbers from 1 to @param mazeSize - 1.
		int row = rand() % (((this->mazeSize - 2) - 1) + 1) + 1;
		int col = rand() % (((this->mazeSize - 2) - 1) + 1) + 1;
		
		//Looks very ugly, but prevents the entrance and exit from being inaccessible in a vast majority of test cases
		if (row == 1 && col == 1 || row == 1 && col == 2 || row == 2 && col == 1 || row == this->mazeSize - 2 && col == this->mazeSize - 3
			|| row == this->mazeSize - 3 && col == this->mazeSize -2 || row == this->mazeSize - 2 && col == this->mazeSize - 2)
		{
			i--;
		}
		else if (this->maze[row][col] == '1')
		{
			i--;
		}
		else
		{
			this->maze[row][col] = '1';
		}
	}

	//'E' will be used to mark the maxe exit
	this->maze[this->mazeSize - 2][this->mazeSize - 2] = 'E';
}

/*
Function: findPath(int x, int y)
Author: Dan Luoma
Description: Used to test if the exit has been found, then determines the next direction the "rat" will go and recursivly calls
findPath with altered coordinates. Will also test for an unsolvable game state.
Inputs: Two ints
*/
void Maze::findPath(int x, int y)
{
	//This tests for backtracking, then marks the space as visited if not already visited
	if (!visited[x][y])
	{
		this->path->addNode(x, y);
		this->visited[x][y] = true;
	}

	//Tests if the "rat" has found the exit
	if (this->maze[x][y] == 'E')
	{
		this->maze[x][y] = 'X';
		this->animation();
		this->end = true;
	}
	else
	{
		//'X' is used to mark a space the "rat" has visited
		this->maze[x][y] = 'X';
	}

	//Attempts to find next direction the "rat" will travel to
	if (this->end != true)
	{
		this->animation();

		//Attempts to move the "rat" right
		if (isClear(x, y + 1))
			this->findPath(x, y + 1);
		//Attempts to move the "rat" down
		else if (isClear(x + 1, y))
			this->findPath(x + 1, y);
		//Attempts to move the "rat" up
		else if (isClear(x - 1, y))
			this->findPath(x - 1, y);
		//Attempts to move the "rat" left
		else if (isClear(x, y - 1))
			this->findPath(x, y - 1);

		//If no next direction is found, attempts to backtrack the "rat"
		else
		{
			//Placing a 'D' will denote a space the "rat" had to backtrack from
			this->maze[x][y] = 'D';
			this->path->deleteRear();

			//Tests if the "rat" has travelled all the way back to the starting position with no more valid moves
			if (this->path->getSize() == 0)
				this->end = false;
			else
			{
				Node<int> *back = this->path->getRear();
				this->findPath(back->First, back->Second);
			}
		}
		
	}
}

/*
Function: animation()
Author: Dan Luoma
Description: Clears the screen, prints the map, then puts the program to sleep for a brief moment to give the
illusion of animation
*/
void Maze::animation()
{
	system("CLS");
	this->printMaze();
	//std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

/*
Function: isClear(int row, int col)
Author: Dan Luoma
Description: Test the char indicated by @param row and @param col to see if it is a valid move for the "rat"
Inputs: Two ints
Outputs: A bool
*/
bool Maze::isClear(int row, int col)
{
	if (this->maze[row][col] == '0' || this->maze[row][col] == 'E')
		return true;
	else
		return false;
}

/*
Function: printMaze()
Author: Dan Luoma
Description: Prints the contents of @param maze
*/
void Maze::printMaze()
{
	for (int i = 0; i < this->mazeSize; i++)
	{
		for (int j = 0; j < this->mazeSize; j++)
		{
			cout << this->maze[i][j] << " ";
		}
		cout << endl;
	}
}
