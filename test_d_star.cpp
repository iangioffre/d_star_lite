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

TEST(AdjacencyListTest, CreateGridTest) {
    AdjacencyList g(9);
    int width = 3;
    int height = 3;
    g.create_grid(width, height);
    for (int i = 0; i < g.vertex_count(); i++) {
        list<int> adj;
        g.adjacent(i, adj);

        // corner nodes
        if (i == 0 || i == g.vertex_count() - 1 || i == width - 1 || i == g.vertex_count() - width) {
            ASSERT_EQ(adj.size(), 2);
        }

        // edge nodes
        else if (i < width || i >= g.vertex_count() - width || i % width == 0 || i % width == width - 1) {
            ASSERT_EQ(adj.size(), 3);
        }

        // interior nodes
        else {
            ASSERT_EQ(adj.size(), 4);
        }
    }
}

TEST(AdjacencyListTest, ObstacleTest) {
    AdjacencyList g(16);
    int width = 4;
    int height = 4;
    g.create_grid(width, height);

    for (int i = 0; i < g.vertex_count(); i++) {
        ASSERT_FALSE(g.is_obstacle(i));
    }

    for (int node = 0; node < g.vertex_count(); node++) {
        g.set_obstacle(node);
        for (int i = 0; i < g.vertex_count(); i++) {
            if (i == node) {
                ASSERT_TRUE(g.is_obstacle(i));
            } else {
                ASSERT_FALSE(g.is_obstacle(i));
            }
        }
        g.remove_obstacle(node);
        for (int i = 0; i < g.vertex_count(); i++) {
            ASSERT_FALSE(g.is_obstacle(i));
        }
    }
}

// TODO: add tests for D* algorithm

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------

TEST(AdjacencyMatrixTest, CreateGridTest) {
    AdjacencyMatrix g(9);
    int width = 3;
    int height = 3;
    g.create_grid(width, height);
    for (int i = 0; i < g.vertex_count(); i++) {
        list<int> adj;
        g.adjacent(i, adj);

        // corner nodes
        if (i == 0 || i == g.vertex_count() - 1 || i == width - 1 || i == g.vertex_count() - width) {
            ASSERT_EQ(adj.size(), 2);
        }

        // edge nodes
        else if (i < width || i >= g.vertex_count() - width || i % width == 0 || i % width == width - 1) {
            ASSERT_EQ(adj.size(), 3);
        }

        // interior nodes
        else {
            ASSERT_EQ(adj.size(), 4);
        }
    }
}

TEST(AdjacencyMatrixTest, ObstacleTest) {
    AdjacencyMatrix g(16);
    int width = 4;
    int height = 4;
    g.create_grid(width, height);

    for (int i = 0; i < g.vertex_count(); i++) {
        ASSERT_FALSE(g.is_obstacle(i));
    }

    for (int node = 0; node < g.vertex_count(); node++) {
        g.set_obstacle(node);
        for (int i = 0; i < g.vertex_count(); i++) {
            if (i == node) {
                ASSERT_TRUE(g.is_obstacle(i));
            } else {
                ASSERT_FALSE(g.is_obstacle(i));
            }
        }
        g.remove_obstacle(node);
        for (int i = 0; i < g.vertex_count(); i++) {
            ASSERT_FALSE(g.is_obstacle(i));
        }
    }
}

// TODO: copy tests for AdjacencyMatrix

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}