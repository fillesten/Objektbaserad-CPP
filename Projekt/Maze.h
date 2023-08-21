#pragma once
#include "iostream"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stack>

/*
Filip Stenegren (fist2000)
2021-10-18
Aiming for a strong G :)!
*/


class Maze
{
	public:

		Maze();

		void DFS(); //generera labyrinten med DFS 
		void Generate();
		
		//output
		void PrintMaze() const;

	private:
		struct node
		{
			node(int y, int x);
			int y;
			int x;

			bool visited;
			bool Up;
			bool Down;
			bool Left;
			bool Right;
		};

		std::vector< std::vector <node>> Row;

		// kollar en specifick nod OM den har grannar
		bool NeighCheck(node n);

		//ger tillbaks en random neigh
		node RandNeigh(node nod);

		//opens gates between nodes
		void Gates(node G, node N);
		

};

