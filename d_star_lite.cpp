//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: d_star_lite.cpp
// DATE: Spring 2021
// DESC: This algorithm will find the shortest path to a
// destination with changing obstacles. For example, a
// robot working its way through a field with other robots.
//----------------------------------------------------------------------

#include "d_star_lite.h"

#include <algorithm>
#include <queue>

const int INF = std::numeric_limits<int>::max();

D_star_lite::D_star_lite(int start_pos, int end_pos, int terrain_width, int terrain_height) {
    int num_nodes = terrain_width * terrain_height;
    terrain = new AdjacencyMatrix(num_nodes);
    terrain->create_grid(terrain_width, terrain_height);
    source = start_pos;
    curr_pos = start_pos;
    destination = end_pos;
    rhs = new int[num_nodes];
    g = new int[num_nodes];

    initialize();
}

void D_star_lite::move() {
    // TODO
}

void D_star_lite::set_obstacle(int node) {
    terrain->set_obstacle(node);
}

void D_star_lite::calculate_key(int s, int* key) {
    key = new int[2];
    key[0]= std::min(g[s], rhs[s]) + h(source, s) + k_m;
    key[1] = std::min(g[s], rhs[s]);
}

void D_star_lite::initialize() {
    int num_nodes = terrain->vertex_count();

    // TODO: U = empty
    k_m = 0;
    for (int i = 0; i < num_nodes; i++) {
        rhs[i] = INF;
        g[i] = INF;
    }
    rhs[destination] = 0;
    // TODO: U.insert(destination, key from calculate_key(destination, key))
}

void D_star_lite::update_vertex(int u) {
    // TODO
}

void D_star_lite::compute_shortest_path() {
    // TODO
}

int D_star_lite::h(int start, int end) {
    return terrain->min_edges_bfs(start, end);
}