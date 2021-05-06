# D* Lite Algorithm

## Algorithm Description
The D* Lite algorithm is an dynamic algorithm that finds a path from a source node to a destination node.  
For example:  
* A robot finding its way through a terrain with other moving obstacles.

At each node, the algorithm computes the shortest path to the destination and takes a step in that path.  
Then, if an obstacle moves or appears, the algorithm will recompute the shortest path given the updated obstacles.

## My Implementation
I implemented D* Lite in C++ using a self-created Graph class as the terrain in a grid with edges between each adjacent node. I did not allow diagonal movement, but by changing the create_grid method in graph.cpp, one could implement diagonal movement.  
Instead of searching for updated edges before updating the nodes, I update every node at each step for ease. For a more efficient approach, check first for the updated edges, then update the nodes on that edge.

## How to Run
Prerequisites: make, cmake, g++  
To run tests in command line:  
1. cmake CMakeLists.txt
1. make
1. ./test_d_star

To implement algorithm:
```
D_star_lite alg(0, 2, 3, 3); // find path from 0 to 2 in a 3x3 (wxh) grid
list<int> path;
while (!alg.destination_reached()) {
    path.push_back(alg.move());
}
```
D_star_lite.move() returns the current node after movement. Thus, after running this code segment, path should contain the path it took to get from source to destination *without* the source node. In this example, path = [1, 2] because the algorithm starts at the source 0, goes to 1, then goes to the destination 2.  
By using `D_star_lite.set_obstacle(int node)` and `D_star_lite.remove_obstacle(int node)` one can add or remove obstacles from the terrain while the algorithm is running, and the algorithm will update at each step to avoid the obstacles.  

## Project Structure
**graph.\*** - graph interface  
**adjacency_list.\*** - a linked list implementation for the graph interface  
**adjacency_matrix.\*** - a 2D array implementation for the graph interface  
**d_star_lite.\*** - the D* Lite algorithm implementation as a class  
**test_d_star.cpp** - the test file for the algorithm and supporting methods  
**CMakeLists.txt** - the CMake file for project compilation  
**\*.pdf** - reports or write-ups for the project  