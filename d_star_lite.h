//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: d_star_lite.h
// DATE: Spring 2021
// DESC: This algorithm will find the shortest path to a
// destination with changing obstacles. For example, a
// robot working its way through a field with other robots.
//----------------------------------------------------------------------

#ifndef D_STAR_LITE_H
#define D_STAR_LITE_H

#include <list>

#include "adjacency_matrix.h"

class D_star_lite {
   public:
    D_star_lite(int start_pos, int end_pos, int terrain_width, int terrain_height);
    void move();
    void set_obstacle(int node);

   private:
    void calculate_key(int s, int* key);
    void initialize();
    void update_vertex(int u);
    void compute_shortest_path();
    int h(int start, int end);

    AdjacencyMatrix* terrain;
    int curr_pos;
    int source;
    int destination;
    int k_m;
    int* rhs;
    int* g;
};

#endif