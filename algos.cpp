/*
Author: Chalet Shelton
Instructor: Dr. Shahrokhi
Date: 4/1/2018
Description:
*/

#include <iostream>
#include <climits>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

void dijkstra(int src, int distance[], const vector<vector<int> >& matrix, int numNodes);
void floyd_warshall(vector<vector<int> >& matrix, int numNodes);

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "****ERROR: usage: ./a.out <name_of_cost_matrix_file>" << endl;
		exit(0);
	}
	//open input file
	ifstream input;
	ofstream results;
	ofstream shortestPath;
	timespec fw_start, fw_end, d_start, d_end;
	
	//remove("results.txt");
	remove("shortestPath.txt");
	
	input.open(argv[1]);

	if(input.is_open())
	{
		results.open("results.txt", ios::app);
		shortestPath.open("shortestPath.txt", ios::app);
		string line;
		
		int numNodes;
		char ch;
		clock_t dijSum, dijElapsed;
		double fwElapsedn = 0.0, dijElapsedn = 0.0;
		double Dtime_elapsedS =0.0, Ftime_elapsedS =0.0;
		input >> line;
		input >> line;
		input >> numNodes;
		
		//create vectors of vectors
		vector<vector<int> > matrix (numNodes, vector<int>(numNodes));
			
		for(int i =0; i < numNodes; i++)
		{
			for(int j =0; j < numNodes; j++)
			{
				input >> matrix[i][j];
			}
		}
				
		//vector for Dijkstra's Algo
		vector<vector<int> > dij(matrix);
			
		//run Dijkstra's
		for(int i =0; i < numNodes; i++)
		{
			int distance[numNodes];
			
			//get the time before the algo
			clock_gettime(CLOCK_REALTIME, &d_start);
			//do the algo
			dijkstra(i, distance, matrix, numNodes);
			// get the time after the algo
			clock_gettime(CLOCK_REALTIME, &d_end);
			//calculate time it took
			dijElapsedn = (d_end.tv_nsec - d_start.tv_nsec);
			Dtime_elapsedS = (d_end.tv_sec - d_start.tv_sec);
			
			for(int j =0; j < numNodes; j++)
			{
				dij[i][j] = distance[j];
			}
		}
			
		//output the cost matrix to a file
		shortestPath <<" numNodes = " << numNodes << endl;
		for(int i =0; i < numNodes; i++)
		{
			for(int j =0; j < numNodes; j++)
			{
				shortestPath << dij[i][j] << " ";
			}
			shortestPath << endl;
		}
		//output the time to comparision file
		results << "+---------------------------------------------------------------------------------------------------------+" << endl;
		results << "| " << setw(4) << "numNodes" << " | " << setw(9) << "Dijkstra nanoseconds" << setw(14) << "Dijkstra seconds" <<" | " << setw(19) << "Floyd-Warshall nanoseconds" << " |" << setw(24) << "Floyd-Warshall seconds" << " |" << endl;
		results << "+---------------------------------------------------------------------------------------------------------+" << endl;
				
		results << "| " << setw(4) << numNodes << " | " << fixed << setw(9) << dijElapsedn << " | "<< fixed << setw(14) << Dtime_elapsedS << " ";
		
		//get the time before the algo
		clock_gettime(CLOCK_REALTIME, &fw_start);
		// Run floyd Warshall	
		floyd_warshall(matrix, numNodes);
		//get time after algo
		clock_gettime(CLOCK_REALTIME, &fw_end);
		//claculate time it took
		fwElapsedn = (fw_end.tv_nsec - fw_start.tv_nsec);
		Ftime_elapsedS = (fw_end.tv_sec - fw_start.tv_sec);
		
		//output the cost matrix to a file
		shortestPath <<" Floyd-Warshall: " << endl;
		for(int i =0; i < numNodes; i++)
		{
			for(int j =0; j < numNodes; j++)
			{
				shortestPath << matrix[i][j] << " ";
			}
		}
			
		shortestPath.close();
		results << "| " << fixed << setw(19) << fwElapsedn <<  "| " << fixed << setw(24) << Ftime_elapsedS << " |" << endl;
		
		results.close();
		input.close();
	}
	else
		cout <<"****** ERROR: problem opening file: " << input << endl;
	return 0;
}
void dijkstra(int src, int distance[], const vector<vector<int> >& matrix, int numNodes)
{

	bool visited[numNodes];
	
	for(int i =0; i < numNodes; i++)
	{
		visited[i] = false;
		distance[i] = matrix[src][i];
	}
	
	visited[src] = true;
	distance[src] =0;
	
	for(int i=0; i < numNodes; i++)
	{
	
		int n, min = INT_MAX;
		// Choose a vertex n, that is unvisited, and whose distance from src is minimum
		for(int j =0; j < numNodes; j++)
		{
			if(visited[j] == false && distance[j] < min)
			{
				n = j;
				min = distance[j];
			}
		}
		
		visited[n] = true;
		// For each neighbor j of n that has not been visited, updated distances
		for(int j =0; j < numNodes; j++)
		{
			if((visited[j] == false) && (distance[j] > distance[n] + matrix[n][j]))
			{
				distance[j] = distance[n] + matrix[n][j];
			}
		}
	}
}

void floyd_warshall(vector<vector<int> >& matrix, int numNodes)
{
	
	for(int i = 0; i <numNodes; i++)
	{
		for(int j =0; j < numNodes; j++)
		{
			for(int k = 0; k < numNodes; k++)
			{
				if(matrix[j][k] > matrix[j][i] + matrix[i][k])
				{
					matrix[j][k] = matrix[j][i] + matrix[i][k];
				}
			}
		}	
	}
}