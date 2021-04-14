//----------------------------------------------------------------------
// Name: Ian Gioffre
// File: test_d_star.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------

#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "graph.h"

using namespace std;

//----------------------------------------------------------------------
// Helper functions for testing
//----------------------------------------------------------------------

void print_graph(const Graph& g) {
    int n = g.vertex_count();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g.has_edge(i, j)) {
                int edge_label;
                g.get_edge(i, j, edge_label);
                cout << "(" << i << "," << edge_label << "," << j << ")" << endl;
            }
        }
    }
}

//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

// TODO: add tests for D* algorithm

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------

// TODO: copy tests for AdjacencyMatrix

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}