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
#include <iostream>

typedef std::pair<int,int> Key;
typedef std::list<std::pair<int,Key>> KeyStack;

const int INF = std::numeric_limits<int>::max();

D_star_lite::D_star_lite(int start_pos, int end_pos, int terrain_width, int terrain_height) {
    int num_nodes = terrain_width * terrain_height;
    terrain = new AdjacencyMatrix(num_nodes);
    terrain->create_grid(terrain_width, terrain_height);
    s_start = start_pos;
    s_last = start_pos;
    curr_pos = start_pos;
    s_goal = end_pos;
    rhs = new int[num_nodes];
    g = new int[num_nodes];

    initialize();
    compute_shortest_path();
}

int D_star_lite::move() {
    if (g[s_start] == INF) {
        return curr_pos; // currently no known path (should change in testing because the obstacles will be removed)
    }

    // s_start = arg of adj(s_start) of min(c(s_start, adj) + g[s_start])
    std::list<int> adj;
    terrain->adjacent(s_start, adj);
    int arg_min;
    int arg_min_cost;
    bool first = true;
    for (int node : adj) {
        if (first) {
            arg_min = node;
            if (g[node] == INF) {
                arg_min_cost = INF;
            } else {
                arg_min_cost = c(s_start, node) + g[node];
            }
            first = false;
        } else {
            int cost;
            if (g[node] == INF) {
                cost = INF;
            } else {
                cost = c(s_start, node) + g[node];
            }
            if (cost < arg_min_cost) {
                arg_min = node;
                arg_min_cost = cost;
            }
        }
    }
    s_start = arg_min;

    curr_pos = s_start;
    if (destination_reached()) {
        return curr_pos;
    }

    // scan for changes (for easier implementation, assume all edges changed)
    k_m = k_m + h(s_last, s_start);
    s_last = s_start;
    
    // for all edges
    for (int node = 0; node < terrain->vertex_count(); node++) {
        update_vertex(node);
    }

    compute_shortest_path();

    return curr_pos; // to track where the alg goes
}

void D_star_lite::set_obstacle(int node) {
    terrain->set_obstacle(node);
}

bool D_star_lite::destination_reached() {
    return curr_pos == s_goal;
}

Key D_star_lite::calculate_key(int s) {
    int term1= std::min(g[s], rhs[s]) + h(s_start, s) + k_m;
    int term2 = std::min(g[s], rhs[s]);
    return std::make_pair(term1, term2);
}

void D_star_lite::initialize() {
    int num_nodes = terrain->vertex_count();
    k_m = 0;

    for (int i = 0; i < num_nodes; i++) {
        rhs[i] = INF;
        g[i] = INF;
    }
    rhs[s_goal] = 0;
    U.push_back(std::make_pair(s_goal, calculate_key(s_goal)));
}

void D_star_lite::update_vertex(int u) {
    if (u != s_goal) {
        std::list<int> adj;
        terrain->adjacent(u, adj);
        int adj_cost[adj.size()];
        int i = 0;
        for (int node : adj) {
            if (g[node] == INF) {
                adj_cost[i] = INF;
            } else {
                adj_cost[i] = c(u, node) + g[node];
            }
            i++;
        }

        rhs[u] = *std::min_element(adj_cost, adj_cost + adj.size());
    }

    for (auto u_pair : U) {
        if (u == u_pair.first) {
            U.remove(u_pair);
            break;
        }
    }
    
    if (g[u] != rhs[u]) {
        U.push_back(std::make_pair(u, calculate_key(u)));
    }
}

void D_star_lite::compute_shortest_path() {
    while ((U.size() > 0 && U.back().second < calculate_key(s_start)) || rhs[s_start] != g[s_start]) {
        Key k_old = U.back().second;
        int u = U.back().first;
        U.pop_back();

        if (k_old < calculate_key(u)) {
            U.push_back(std::make_pair(u, calculate_key(u)));
        } else if (g[u] > rhs[u]) {
            g[u] = rhs[u];
            std::list<int> adj;
            terrain->adjacent(u, adj);
            for (int s : adj) {
                update_vertex(s);
            }
        } else {
            g[u] = INF;
            std::list<int> adj;
            terrain->adjacent(u, adj);
            adj.push_back(u);
            for (int s : adj) {
                update_vertex(s);
            }
        }
    }
}

int D_star_lite::h(int start, int end) {
    return terrain->min_edges_bfs(start, end);
}

int D_star_lite::c(int node1, int node2) {
    int edge;
    if (node1 < node2) {
        terrain->get_edge(node1, node2, edge);
    } else {
        terrain->get_edge(node2, node1, edge);
    }
    return edge;
}