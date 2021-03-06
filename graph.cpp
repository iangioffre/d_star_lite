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
#include <queue>

typedef std::list<int> List;
typedef std::queue<int> Queue;
const int MAX_INT = std::numeric_limits<int>::max();

//----------------------------------------------------------------------
// Project graph operations (D* lite search algorithm)
//----------------------------------------------------------------------

int Graph::min_edges_bfs(int src, int dst) const {
    Map tree;
    tree[src] = -1;
    Map discovered;
    for (int i = 0; i < vertex_count(); i++) {
        discovered[i] = false;
    }
    discovered[src] = true;
    Queue q;
    q.push(src);
    bool isFound = false;  // true if dst is found

    while (q.size() > 0 && !isFound) {
        int u = q.front();
        q.pop();
        List adj;
        adjacent(u, adj);
        for (int v : adj) {
            // check if node has been discovered yet
            if (!discovered[v]) {
                discovered[v] = true;
                tree[v] = u;
                q.push(v);
                if (v == dst) {
                    isFound = true;
                    break;
                }
            }
        }
    }

    // if dst has been found, populate the list with the path from src to dst
    List path;
    if (isFound) {
        path.clear();
        int currNode = dst;
        do {
            path.push_front(currNode);
            currNode = tree[currNode];
        } while (currNode != src);
        path.push_front(currNode);
    } else {
        path.clear();
    }

    int num_edges = path.size() - 1;
    if (num_edges < 0) {
        num_edges = 0;
    }
    return num_edges;
}

void Graph::create_grid(int width, int height) {
    grid_width = width;
    grid_height = height;
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