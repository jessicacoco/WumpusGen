#include <iostream>
#include <fstream>
#include <stdlib.h>    
#include <time.h> 
#include <string>

#include "node.cpp"
#include "MarkSolver.cpp"
#include <random>
using namespace std;
typedef vector< vector<Node> > game;
// 0==empty 1==pit 2==wumups 3==gold
game maptrans(vector<vector<int> > numap){
	game themap;
	int wallsize=numap.size();
	for(int i =0; i<wallsize;i++){
		vector<Node> line;
		for(int j=0;j<wallsize;j++){
			if(numap[i][j]==0) line.push_back(Node(i,j,"e",wallsize));
			else if(numap[i][j]==1) line.push_back(Node(i,j,"p",wallsize));
			else if(numap[i][j]==2) line.push_back(Node(i,j,"w",wallsize));
			else if(numap[i][j]==3) line.push_back(Node(i,j,"g",wallsize));
			else line.push_back(Node(i,j,"e",wallsize));
		}
		themap.push_back(line);
	}
	
	for(int i =0; i<wallsize;i++){		
		for(int j=0;j<wallsize;j++){
		
			if(numap[i][j]==1) {
				if(i+1<wallsize) themap[i+1][j].breeze=true;
				if(j+1<wallsize) themap[i][j+1].breeze=true;
				if(i-1>=0) themap[i-1][j].breeze=true;
				if(j-1>=0) themap[i][j-1].breeze=true;
			}
			if(numap[i][j]==2) {
				if(i+1<wallsize) themap[i+1][j].stench=true;
				if(j+1<wallsize) themap[i][j+1].stench=true;
				if(i-1>=0) themap[i-1][j].stench=true;
				if(j-1>=0) themap[i][j-1].stench=true;
			}
			if(numap[i][j]==3) {
				if(i+1<wallsize) themap[i+1][j].glitter=true;
				if(j+1<wallsize) themap[i][j+1].glitter=true;
				if(i-1>=0) themap[i-1][j].glitter=true;
				if(j-1>=0) themap[i][j-1].glitter=true;
			}

		}
		
	}
	
	return themap;
}

vector<vector<int> > randgrid(int size,int pits){
    srand(time(NULL));
    vector<vector<int> > grid;
    // create 1 board without any stuff in it
    for(int i=0;i<size;i++){
    	vector<int> line;
    	grid.push_back(line);
    	for(int j=0;j<size;j++){
    		grid[i].push_back(0);
		}
	}
	
	bool alreadyput=false;
	// put in gold
	while(!alreadyput){
		int x=rand()%size;
		int y=rand()%size;
		if((x!=y||x!=0)&&grid[x][y]==0){
			grid[x][y]=3;
			alreadyput=true;
			
		}
	}
	alreadyput=false;
	//put in wumpus;
	while(!alreadyput){
		int x=rand()%size;
		int y=rand()%size;
		if((x!=y||x!=0)&&!(x==0&&y==1)&&!(x==1&&y==0)&&grid[x][y]==0){
			grid[x][y]=2;
			alreadyput=true;
			
		}
	}
	alreadyput=false;
	//put in pits
	if(pits>=size*size-6){
    	cerr<<"too many pits";
    	return grid;
	}
	for(int num=0;num<pits;num++){
		alreadyput=false;
		while(!alreadyput){
			int x=rand()%size;
			int y=rand()%size;
			if((x!=y||x!=0)&&!(x==0&&y==1)&&!(x==1&&y==0)&&grid[x][y]==0){
				grid[x][y]=1;
				alreadyput=true;
			
			}
		}
	}
	return grid;
}

void printgrid(vector<vector<int> > grid,int size ){
	cout<<endl;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<grid[size-i-1][j];
		}
		cout<<endl;
	}
}
// My goal is to consolidate everything we are doing for the generator into one place
// so I am using the generatorIdeas functions to create the grid
// and the nodes class to add nodes to the grid to create something that can be more
// interactive and respond then prompted to

// I am not sure what we want to output, so it is easy to return the grid of strings or nodes 
// It is possible to just 

int main()   
{ 
	int size;
	int pits;
	int diffy;
	std::cout << "Enter the size:"; // enter the size of the matrix
	std::cin >> size;
	std::cout << "Enter the number of pits:"; // enter the # of pits
	std::cin >> pits;
	std::cout << "Enter the level of difficulty:";// enter the difficulty	-1 cantsolve
			//0 easy, which doesnt involve glitter check and shoot wumpus
			//1 medium, which involve glitter check
			//2 hard which involve shooting down the wumpus
			//3 extreme, which involve both shooting down the wumpus and glitter check
	std::cin>> diffy;
	std::vector<vector<int> > grid=randgrid(size,pits);
	while(!marksolver(maptrans(grid),size)||!(diffy==eval(maptrans(grid),size))){
		grid=randgrid(size,pits);
	}
	cout<<"Found difficulty: "<<diffy<<endl;
	printgrid(grid,size);


	return  0;
} 

