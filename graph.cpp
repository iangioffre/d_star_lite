//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: graph.cpp
// DATE: Spring 2021
// DESC: A directed graph consists of vertices and edges. Each vertex
// has a unique identifier (from 0 to n-1) and each edge has a
// (non-unique) integer label.
//----------------------------------------------------------------------

#include "graph.h"

#include <algorithm>
#include <list>

typedef std::list<int> List;
const int MAX_INT = std::numeric_limits<int>::max();

//----------------------------------------------------------------------
// Project graph operations (D* lite search algorithm)
//----------------------------------------------------------------------

void Graph::create_grid(int width, int height) {
    for (int node = 0; node < vertex_count(); node++) {
        // below
        if (node < vertex_count() - width) {
            set_edge(node, 1, node + width);
        }

        // right
        if (node % width != width - 1) {
            set_edge(node, 1, node + 1);
        }
    }
}

void Graph::set_obstacle(int node) {
    List adj;
    adjacent(node, adj);

    for (int adj_node : adj) {
        if (adj_node < node) {
            int edge;
            get_edge(adj_node, node, edge);
            if (edge == 1) {
                remove_edge(adj_node, node);
                set_edge(adj_node, MAX_INT, node);
            }
        } else {
            int edge;
            get_edge(node, adj_node, edge);
            if (edge == 1) {
                remove_edge(node, adj_node);
                set_edge(node, MAX_INT, adj_node);
            }
        }
    }
}

bool Graph::is_obstacle(int node) const {
    bool is_obstacle = true;
    List adj;
    adjacent(node, adj);

    for (int adj_node : adj) {
        if (adj_node < node) {
            int edge;
            get_edge(adj_node, node, edge);
            if (edge == 1) {
                is_obstacle = false;
            }
        } else {
            int edge;
            get_edge(node, adj_node, edge);
            if (edge == 1) {
                is_obstacle = false;
            }
        }
    }

    return is_obstacle;
}

void Graph::remove_obstacle(int node) {
    if (is_obstacle(node)) {
        List adj;
        adjacent(node, adj);

        for (int adj_node : adj) {
            if (adj_node < node) {
                int edge;
                get_edge(adj_node, node, edge);
                if (edge == MAX_INT) {
                    remove_edge(adj_node, node);
                    set_edge(adj_node, 1, node);
                }
            } else {
                int edge;
                get_edge(node, adj_node, edge);
                if (edge == MAX_INT) {
                    remove_edge(node, adj_node);
                    set_edge(node, 1, adj_node);
                }
            }
        }
    }
}

//----------------------------------------------------------------------
// TODO: description
//
// Conditions: TODO: conditions
//
// Input:
//  TODO: input details
//
// Output:
//  TODO: output details
//
// Returns: TODO: return details
//----------------------------------------------------------------------
void Graph::d_star_lite_shortest_path(int src, int dst, List& path) const {
}

// helper functions for d* lite algorithm
void Graph::calculate_keys() const {
}

void Graph::initialize() const {
}

void Graph::update_vertex() const {
}

void Graph::compute_shortest_path() const {
}