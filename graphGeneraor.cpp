/*
Author: Chalet Shelton
Instructor: Dr. Shahrokhi
Date: 4/1/2018
Description:
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout << "****ERROR: usage: ./a.out <max_num_of_nodes> <max_weight_of_edges>" << endl;
		exit(0);
	}
	//remove("graphs.txt");
	//seed random number
	srand(time(0));
	
	ofstream output;
	
	unsigned int maxWeight = atoi(argv[2]);
	unsigned int maxNumNodes = atoi(argv[1]);

	
	//generate cost matrix
	cout <<"Generating matricies" << endl;
	
	//generate number of nodes from 50-1000
	int numNodes = rand() % ((maxNumNodes - 49) + 50);
	
	//make vector of vectors
	vector<vector<int> > matrix (numNodes, vector<int>(numNodes));
		
	//initilize matrix
	
	for(int j =0; j < numNodes; j++)
	{
		for(int k =0; k < j; k++)
		{
			if(j == k)
				matrix[j][k] = 0;
			else
				matrix[j][k] = matrix[k][j] = rand() % maxWeight + 1;
		}
	}
	
	output.open("graphs.txt");
		
	//write to file
	if(output.is_open())
	{
		output << "numNodes = "<< numNodes << endl;
		for(int i =0; i < numNodes; i++)
		{
			for(int j =0; j < numNodes; j++)
			{
				if(j == (numNodes -1))
					output << matrix[i][j] << " ";
				else
					output << matrix[i][j] << " ";
			}
			output << endl;
		}
		output.close();
	}
	else
		cout << "*****ERROR: There was a problem opening the file." << endl;
		
	cout <<"Complete!"<<endl;
	
	return 0;
}