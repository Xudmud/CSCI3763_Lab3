# CSCI3763_Lab3
--------------------------------------------------------------------------------
Name:       Gregory Wicklund
Student ID: 810906774
Class:      Intro to Computer Networks, Spring 2019
Due Date:   6 May 2019
Minimum Spanning Tree simulation
--------------------------------------------------------------------------------

Instructions:
Run make from the program root
$ make

Run the compiled program, giving an argument for the file to read.
$ ./wic6774mst <input file>

Source for Prim's algorithm implementation:
https://www.tutorialspoint.com/data_structures_algorithms/prims_spanning_tree_algorithm.htm

The input file is in the following format:
First line gives the number of nodes in the tree
The next lines give the connections between nodes and the cost of that connection.  
Example file is at the end of the README.  

An arbitrarily large number (2^30 in the example input files) is used to indicate  
that there is no connection between two nodes.  This, along with self-connections
are set to 0 in the program to indicate there is no edge present.

Please note that this program assumes a minimum spanning tree can be created from
a given set of nodes and edges. There is no error checking done to see if such a
tree is impossible to create.  

This implementation makes use of Prim's algorithm to build the minimum spanning tree.  
Starting from the root node, the cheapest node that would connect to the tree
that isn't already in the tree is added. This process is repeated, with backtracking
to previous nodes in the case no valid nodes exist from the current position.  

Example input file  

6  
1 1 0
1 2 2
1 3 1
1 4 5
1 5 1073741824
1 6 1073741824
2 1 2
2 2 0
2 3 5
2 4 1
2 5 1073741824
2 6 1073741824
3 1 1  
3 2 5
3 3 0
3 4 3
3 5 1
3 6 1073741824
4 1 5
4 2 1
4 3 3
4 4 0
4 5 2
4 6 5
5 1 1073741824
5 2 1073741824
5 3 1
5 4 2
5 5 0
5 6 2
6 1 1073741824
6 2 1073741824
6 3 1073741824
6 4 5
6 5 2
6 6 0
