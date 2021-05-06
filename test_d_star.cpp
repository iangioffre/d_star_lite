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
#include "d_star_lite.h"

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

void print_path(list<int> path) {
    while(!path.empty()) {
        cout << path.front() << " ";
        path.pop_front();
    }
    cout << endl;
}

//----------------------------------------------------------------------
// Helper Tests
//----------------------------------------------------------------------

TEST(HelperTest, CreateGridTest) {
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

TEST(HelperTest, ObstacleTest) {
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

TEST(HelperTest, MinEdgesBFSTest) {
    AdjacencyMatrix g(5);
    g.set_edge(0, 0, 1);
    g.set_edge(0, 0, 3);
    g.set_edge(1, 0, 3);
    g.set_edge(1, 0, 2);
    g.set_edge(2, 0, 4);
    int dists[5];
    for (int i = 0; i < g.vertex_count(); i++) {
        dists[i] = g.min_edges_bfs(0, i);
    }

    ASSERT_EQ(dists[0], 0);
    ASSERT_EQ(dists[1], 1);
    ASSERT_EQ(dists[2], 2);
    ASSERT_EQ(dists[3], 1);
    ASSERT_EQ(dists[4], 3);
}

//----------------------------------------------------------------------
// Algorithm Tests
//----------------------------------------------------------------------

TEST(AlgorithmTest, NoObstacleDStarTest0to2) {
    D_star_lite alg(0, 2, 3, 3); // start 0, end 2, 3x3 terrain
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(2, path.size());
    ASSERT_EQ(1, path.front());
    path.pop_front();
    ASSERT_EQ(2, path.front());
}

TEST(AlgorithmTest, NoObstacleDStarTest5to3) {
    D_star_lite alg(5, 3, 3, 3); // start 5, end 3, 3x3 terrain
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(2, path.size());
    ASSERT_EQ(4, path.front());
    path.pop_front();
    ASSERT_EQ(3, path.front());
}

TEST(AlgorithmTest, NoObstacleDStarTest0to8) {
    D_star_lite alg(0, 8, 3, 3); // start 0, end 8, 3x3 terrain
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(4, path.size());
}

TEST(AlgorithmTest, NoObstacleDStarTest0to15) {
    D_star_lite alg(0, 15, 4, 4); // start 0, end 15, 3x3 terrain
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(6, path.size());
}

TEST(AlgorithmTest, NoObstacleDStarTest1to10) {
    D_star_lite alg(1, 10, 4, 3); // start 0, end 8, 4x3 (wxh) terrain
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(3, path.size());
}

// SO - static obstacle, VO variable obstacle

TEST(AlgorithmTest, ObstacleSO_1) {
    D_star_lite alg(0, 2, 3, 3);
    alg.set_obstacle(1);
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(4, path.size());
}

TEST(AlgorithmTest, ObstacleSO_5) {
    D_star_lite alg(1, 9, 4, 3);
    alg.set_obstacle(1);
    list<int> path;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(4, path.size());
}

TEST(AlgorithmTest, ObstacleVO_2) {
    D_star_lite alg(0, 3, 4, 3);
    alg.set_obstacle(2);
    list<int> path;
    int remove_vo_2 = true;
    while(!alg.destination_reached()) {
        if (remove_vo_2) {
            alg.remove_obstacle(2);
            remove_vo_2 = false;
        }
        int curr_node = alg.move();
        path.push_back(curr_node);
    }
    ASSERT_EQ(3, path.size());
}

TEST(AlgorithmTest, ObstacleVO_5) {
    D_star_lite alg(0, 2, 3, 3);
    alg.set_obstacle(1);
    list<int> path;
    int remove_vo_1 = true;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
        if (remove_vo_1) {
            alg.remove_obstacle(1);
            remove_vo_1 = false;
        }
    }
    ASSERT_EQ(4, path.size());
}

TEST(AlgorithmTest, ObstacleNoPath33) {
    D_star_lite alg(0, 2, 3, 3);
    alg.set_obstacle(1);
    alg.set_obstacle(3);
    list<int> path;
    int last_node;
    int same_spot_for = 0;
    bool no_path_found = false;
    while(!alg.destination_reached()) {
        int curr_node = alg.move();
        path.push_back(curr_node);
        if (last_node == curr_node) {
            same_spot_for++;
        }
        if (same_spot_for == 5) {
            no_path_found = true;
            break;
        }
        last_node = curr_node;
    }
    ASSERT_TRUE(no_path_found);
}

// TODO: create tests for D Star Lite algorithm

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}