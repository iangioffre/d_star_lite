//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: graph.cpp
// DATE: Spring 2021
// DESC: A directed graph consists of vertices and edges. Each vertex
// has a unique identifier (from 0 to n-1) and each edge has a
// (non-unique) integer label.
//----------------------------------------------------------------------

#include "graph.h"

#include <list>

typedef std::list<int> List;

//----------------------------------------------------------------------
// Project graph operations (D* lite search algorithm)
//----------------------------------------------------------------------

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