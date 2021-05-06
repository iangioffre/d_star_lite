# D* Lite Algorithm

## Algorithm Description
The D* Lite algorithm is an dynamic algorithm that finds a path from a source node to a destination node.  
For example:  
* A robot finding its way through a terrain with other moving obstacles.

At each node, the algorithm computes the shortest path to the destination and takes a step in that path.  
Then, if an obstacle moves or appears, the algorithm will recompute the shortest path given the updated obstacles.

## My Implementation
I implemented D* Lite in C++ using a self-created Graph class as the terrain in a grid with edges between each adjacent node.  
Instead of searching for updated edges before updating the nodes, I update every node at each step for ease. For a more efficient approach, check first for the updated edges, then update the nodes on that edge.

## Project Structure
**graph.\*** - graph interface  
**adjacency_list.\*** - a linked list implementation for the graph interface  
**adjacency_matrix.\*** - a 2D array implementation for the graph interface  
**d_star_lite.\*** - the D* Lite algorithm implementation as a class  
**test_d_star.cpp** - the test file for the algorithm and supporting methods  
**CMakeLists.txt** - the cmake file for project compilation  
**\*.pdf** - reports or write-ups for the project  