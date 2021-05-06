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
#include <utility>

#include "adjacency_matrix.h"

typedef std::pair<int,int> Key;
typedef std::list<std::pair<int,Key>> KeyStack;

class D_star_lite {
   public:
    D_star_lite(int start_pos, int end_pos, int terrain_width, int terrain_height);
    int move();
    void set_obstacle(int node);
    bool destination_reached();

   private:
    Key calculate_key(int s);
    void initialize();
    void update_vertex(int u);
    void compute_shortest_path();
    int h(int start, int end);
    int c(int node1, int node2);

    AdjacencyMatrix* terrain;
    KeyStack U;
    int s_start;
    int curr_pos;
    int s_last;
    int s_goal;
    int k_m;
    int* rhs;
    int* g;
};

#endif