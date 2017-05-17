/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "png.h"
#include "dsets.h"

using namespace std;
using std::queue;
using std::vector;
using std::pair;


class SquareMaze
{

	public:
	
		SquareMaze();
		
		void makeMaze(int width, int height);
		
		bool canTravel(int x, int y, int dir) const;
		
		void setWall(int x, int y, int dir, bool exists);
		
		vector<int> solveMaze();

		PNG* drawMaze() const;
		
		PNG* drawMazeWithSolution();

	private:
		int w;
		int h;
		DisjointSets SM;
		int dest_x;
		int dest_y;
		class Square
		{
			public:
				Square(){
					rightWalls = true;
					bottomWalls = true;
					
				}
				bool rightWalls;
				bool bottomWalls;
				bool visited;
		};
		 

		vector<Square> maze;

		vector<int> direction; 
		
		
		
};	
#endif
