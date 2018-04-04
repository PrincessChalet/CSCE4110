Chalet Shelton

To successfully run the comparison's you must compile the graph generator first.
Then compile the algorithms comparison program.
    Compile the graph generator: 		g++ grapGeneraor.cpp -o generator
    Compile the algorithms comparison:  g++ algos.cpp -lrt -o comparison

	
To execute you must first execute the graph generator, unless you have your own cost matrix you'd
like to run. The graph generator ONLY generates one graph at a time and takes in 2 parameters. The size of the
the cost matrix and the max weight of nodes you'd like. Both MUST be inputed to correctly run the program. 
***NOTE: if running you're own cost matrix, your file MUST be in the format: <string> <string> <int>, then data. 
For instance, the first line that's generated in my graph function is the size of the matrix which looks like
numNodes = <int>. My program will first read the first 2 strings, and then read the int so it knows the n x n size
of the cost matrix. **** END OF NOTE. Next you must execute the algorithm comparison program which takes in a file

name parameter.
    Execute the graph generator: 				./generator <max_num_of_nodes> <max_weight_of_edges>
    Execute the algorithm comparison program: 	./comparison <name_of_cost_matrix_file>

	
Known Issues:

1. May occasionally get a negative number in nano seconds field. If so just run again.
2. The results.txt file is appended to, so for each run that you do it adds to the file.
If you want to get rid of the results.txt file uncomment line 36, where it says remove("results.txt");.
The appendage was intentional for testing purposes. 
3. The 2 parameter, < max_num_of_nodes> is used to randomly generate the size of the cost matrix. It will not be the actual
size of the cost matrix.