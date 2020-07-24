#include <iostream>
#include <fstream>
#include <stdlib.h>    
#include <time.h> 
#include <string>
#include <thread>
#include <mutex> 
#include "node.cpp"
#include "MarkSolver.cpp"
#include <random>
#include <ctime>
#include <windows.h>
using namespace std;
typedef vector< vector<Node> > game;

// global viables for the thread to use
mutex thelock;
vector<vector<vector<int> > > answer;
int size=4;
int pits=2;
int diffy=3;



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

vector<vector<int> > randgrid(int size,int pits,int tid){
	
    srand((int(clock()*10000)+tid)*tid);
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

void findmap(int tid){
	vector<vector<int> > grid=randgrid(size,pits,tid);
	while(!marksolver(maptrans(grid),size)||!(diffy==eval(maptrans(grid),size))){
		grid=randgrid(size,pits,tid);
		if(answer.size()!=0) return;
	}
	thelock.lock();
	if(answer.size()==0){
		answer.push_back(grid);
	}
	thelock.unlock();
	return;
}



// My goal is to consolidate everything we are doing for the generator into one place
// so I am using the generatorIdeas functions to create the grid
// and the nodes class to add nodes to the grid to create something that can be more
// interactive and respond then prompted to

// I am not sure what we want to output, so it is easy to return the grid of strings or nodes 
// It is possible to just 

int main()   
{ 	
	for(int threadsnum=1;threadsnum<=16;threadsnum++){
		cout<<"Threadsnum "<<threadsnum<<":"<<endl;
		double average=0;
		for(int count=0;count<10;count++){
			clock_t start=clock();
			vector<thread> threads;
			for(int t=0;t<threadsnum;t++){
				threads.push_back(thread(findmap,t*t+1));
			}
			for(int t=0;t<threadsnum;t++){
				threads[t].join();
			}
			double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			cout<<duration<<endl;
			average+= duration;
			printgrid(answer[0],size);
			while(answer.size()!=0) answer.pop_back();
			Sleep(2000);
		}
		cout<<endl<<"Average : "<<average/10<<endl<<endl;
		
	}
	


	return  0;
} 

