/* Your code here! */
#include "maze.h"

SquareMaze::SquareMaze() 
{
}

void SquareMaze::makeMaze(int width, int height) 
{
	w = width;
	h = height;
	int size = width*height;
	
	SM.addelements(size);
	
	maze = vector<Square>();
	for (int i = 0; i < size; i++) {
		maze.push_back(Square());
	}
/*
	int idx = 0;
	while(idx<size) {
		maze.push_back(Cell());
		idx++;
	}


	vector<int> temp;
	for (int i=0; i<size*2; i++) {
		temp.push_back(i);
	}		
*/
	srand(time(NULL));

	int temp = 0;
	int count = size-1;
	int x, y;
	int idx;

	
	while (temp != count) {
		x = rand()%w;
		y = rand()%h;
		idx = x+y*w;
		bool flag = rand()%2;
	
		if (flag && ((x+1)< w)) {

			int randN = x*h+y;
			int randNN = (x+1)*h+y;
			if (SM.find(randN) != SM.find(randNN)) {
				SM.setunion(SM.find(randN), SM.find(randNN));
				maze[idx].rightWalls = false;
				temp++;
			}
		}
		if (!flag && ((y+1)< h)) {
			int randN = x*h+y;
			int randNN = x*h+(y+1);
			if (SM.find(randN) != SM.find(randNN)) {
				SM.setunion(SM.find(randN), SM.find(randNN));
				maze[idx].bottomWalls = false;
				temp++;
			}
		}
	}


/*
	random_shuffle(temp.begin(), temp.end());

	vector<int>::iterator randN;

	//while(!temp.empty()) {
		for (randN = temp.begin(); randN != temp.end(); randN++){
			if ((*randN)<size) {
				if ((*randN+1)%width != 0) {
					if (SM.find(*randN) != SM.find(*randN+1)) {
						SM.setunion((*randN),(*randN)+1);
						maze[(*randN)].rightWalls = false;
					}
				}
	
			}
			else if ((*randN) >= size) {
				if ((*randN)<(size*2-width)) {
					int i = (*randN) - size;
					if (SM.find(i) != SM.find(i+width)) {
						SM.setunion(i,i+width);
						maze[i].bottomWalls = false;
					}					
				}
			}
				
		}
		
	//}
*/	
}

//dir 0 = x+1;
//dir 1 = y+1;
//dir 2 = x-1;
//dir 3 = y-1
bool SquareMaze::canTravel(int x, int y, int dir) const 
{
	if (x<0 || y<0 || x>=w ||y>=h)
		return false;
	if(dir == 0) { 
		if (x != w-1) {
			return !maze[x+y*w].rightWalls;
		}
		return false;
	}

	if (dir ==1) {
		if (y != h-1) {
			return !maze[x+y*w].bottomWalls;
		}
		return false;
	}
	
	if (dir == 2) {
		if (x != 0) {
			return !maze[(x-1)+y*w].rightWalls;
		}
		return false;
	}
	
	if (dir == 3) {
		if (y != 0) {
			return !maze[x+(y-1)*w].bottomWalls;
		}
		return false;
	}
	return false;
	
	
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) 
{
	if (dir == 0) {
		if (x != w-1){
			maze[x+y*w].rightWalls = exists;
		}
	}
	if (dir ==1) {
		if (y != h-1){		
			maze[x+y*w].bottomWalls = exists;
		}
	}
}

vector <int> SquareMaze::solveMaze()
{	
	vector<int> solution;	

	queue<int> temp; 
	vector<int> a(h,0);
	vector<vector<int>> path(w,a);

	for (int i = 0; i<w; i++) {
		for (int j = 0; j<h; j++) {
			maze[i+j*w].visited = false;
		}
	}
	
	int front;
	int x,y;
	temp.push(0);
	maze[0+0*w].visited = true;
	path[0][0] =1;
//<< "enter solve"<<endl;

	while (!temp.empty()) {
		front = temp.front();
		temp.pop();
		x = front%w;
		y = front/w;

//cout<<"start whil"<<endl;

		if (canTravel(x,y,0) && maze[(x+1)+y*w].visited==false) {
			path[x+1][y] = path[x][y]+1;
			maze[(x+1)+y*w].visited = true;
			temp.push((x+1)+y*w);
			//<<"righ finish"<<endl;
		}
//cout<<"right finish"<<endl;

		if (canTravel(x,y,1) && maze[x+(y+1)*w].visited==false) {
			path[x][y+1] = path[x][y]+1;
			maze[x+(y+1)*w].visited = true;
			temp.push(x+(y+1)*w);
			//<<"down"<<endl;
		}
	//<<"down finish"<<endl;
		if (canTravel(x,y,2) && maze[(x-1)+y*w].visited==false) {
			path[x-1][y] = path[x][y]+1;
			maze[(x-1)+y*w].visited = true;
			temp.push((x-1)+y*w);
			//cout<<"left"<<endl;
		}
		//cout<<"left finish"<<endl;
		if (canTravel(x,y,3) && maze[x+(y-1)*w].visited==false) {			
			path[x][y-1] = path[x][y]+1;
			maze[x+(y-1)*w].visited = true;
			temp.push(x+(y-1)*w);
		//cout<<"up"<<endl;
		}
	//cout<<"up finish"<<endl;
	}
	//int max = 0;
	x=0;
	int max = 0;	
	//int max = w;
	for (int i = 0; i < w; i++) {
		if(path[i][h-1] > path[x][h-1]) {
			x = i;
			//max = (w*h)-w+i;
			
		}
	}
	
	y=h-1;

	dest_x = x;
	dest_y = y;
	//vector<int> dir;
	//for (int i = 0; i < path[x][y]; i++) {
	while(x>0 || y>0) {
		if (canTravel(x,y,0) && (path[x+1][y] == path[x][y]-1)) {				
			//dir.push_back(2);
			solution.insert(solution.begin(),2);
			x++;	
		}
		
		if (canTravel(x,y,1) && (path[x][y+1] == path[x][y]-1)) {				
			//dir.push_back(3);
			solution.insert(solution.begin(),3);
			y++;
		}
		
		if (canTravel(x,y,2) && (path[x-1][y] == path[x][y]-1)) {				
			//dir.push_back(0);
			solution.insert(solution.begin(),0);
			x--;
		}
		
		if (canTravel(x,y,3) && (path[x][y-1] == path[x][y]-1)) {				
			//dir.push_back(1);
			solution.insert(solution.begin(),1);
			y--;
		}
		
	
	}

	/*
	for (int i = dir.size()-1; i >= 0; i--) {
	
		solution.push_back(dir[i]);
		dir.pop_back();
	}
*/

	return solution;


}


PNG *SquareMaze::drawMaze() const 
{
	int PNG_w = w*10+1;
	int PNG_h = h*10+1;
	PNG *Maze = new PNG(PNG_w, PNG_h);


	
	for (int i = 0; i < PNG_h; i++) {
		(*Maze)(0,i)->red = 0;
		(*Maze)(0,i)->green = 0;
		(*Maze)(0,i)->blue = 0;
	}
	for (int i = 10; i < PNG_w; i++) {
		(*Maze)(i,0)->red = 0;
		(*Maze)(i,0)->green = 0;
		(*Maze)(i,0)->blue = 0;
	}

	
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int idx = w*y+x;
			if (maze[idx].rightWalls) {
				for (int k = 0; k <=10; k++) {
					(*Maze)((x+1)*10,y*10+k)->red = 0;
					(*Maze)((x+1)*10,y*10+k)->green = 0;
					(*Maze)((x+1)*10,y*10+k)->blue = 0;
				}
			}
			if (maze[idx].bottomWalls) {
				for (int k = 0; k <=10; k++) {
					(*Maze)(x*10+k,(y+1)*10)->red = 0;
					(*Maze)(x*10+k,(y+1)*10)->green = 0;
					(*Maze)(x*10+k,(y+1)*10)->blue = 0;
				}
			}
		}
	}

	return Maze;
}

PNG *SquareMaze::drawMazeWithSolution() 
{
	//cout<<"endter drawsolution"<<endl;
	PNG * drawSol= drawMaze();
	//cout<<"1"<<endl;
	vector<int> Sol = solveMaze();
	//cout<<"2"<<endl;
	int x = 5;
	int y = 5;
	//cout<<"before"<<endl;
	int s_size = Sol.size();
	//cout<<s_size<<endl;

	for (size_t i = 0; i<Sol.size();i++) {
		//cout<<"enter for loop"<<endl;
		if(Sol[i] == 0) {
			for (int k = 0; k <=10; k++) {
				(*drawSol)(x+k,y)->red = 255;
				(*drawSol)(x+k,y)->green = 0;
				(*drawSol)(x+k,y)->blue = 0;
			}
			x += 10;
			//cout<<"right"<<endl;
		}

		if (Sol[i] == 1) {
			for (int k = 0; k <= 10; k++) {
				(*drawSol)(x,y+k)->red = 255;
				(*drawSol)(x,y+k)->green = 0;
				(*drawSol)(x,y+k)->blue = 0;

			}
			y += 10;
			//cout<<"down"<<endl;
		}

		if (Sol[i] == 2){
			for(int k = 0; k <= 10; k++) {
				(*drawSol)(x-k,y)->red = 255;
				(*drawSol)(x-k,y)->green = 0;
				(*drawSol)(x-k,y)->blue = 0;
	
			}
			
			x -= 10;
			//cout<<"left"<<endl;
		}
		
		if (Sol[i] == 3) {
			for (int k = 0; k <= 10; k++) {
				(*drawSol)(x,y-k)->red = 255;
				(*drawSol)(x,y-k)->green = 0;
				(*drawSol)(x,y-k)->blue = 0;
						
			}
			y -= 10;
			//cout<<"up"<<endl;
		
		}
	}
	

	for (int k =1; k<=9; k++) {
		(*drawSol)(dest_x*10+k, (dest_y+1)*10)->red = 255;
		(*drawSol)(dest_x*10+k, (dest_y+1)*10)->green = 255;
       		(*drawSol)(dest_x*10+k, (dest_y+1)*10)->blue = 255;

	}	


	return drawSol;
}


















