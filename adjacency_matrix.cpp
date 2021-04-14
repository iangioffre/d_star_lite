//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: adjacency_matrix.cpp
// DATE: Spring 2021
// DESC: Adjacency matrix implementation of the graph interface
//----------------------------------------------------------------------

#include "adjacency_matrix.h"

// default constructor
AdjacencyMatrix::AdjacencyMatrix(int vertex_count) {
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    adj_matrix = new int*[vertex_count*vertex_count];
    for (int i = 0; i < vertex_count * vertex_count; i++) {
        adj_matrix[i] = nullptr;
    }
}

// destructor
AdjacencyMatrix::~AdjacencyMatrix() {
    make_empty();
}

// copy constructor
AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& rhs) {
    number_of_vertices = 0;
    number_of_edges = 0;
    adj_matrix = nullptr;
    *this = rhs;
}

// assignment operator
AdjacencyMatrix& AdjacencyMatrix::operator=(const AdjacencyMatrix& rhs) {
    if (this != &rhs) {
        make_empty();
        number_of_vertices = rhs.number_of_vertices;
        adj_matrix = new int*[number_of_vertices * number_of_vertices];
        for (int i = 0; i < number_of_vertices * number_of_vertices; i++) {
            adj_matrix[i] = nullptr;
        }
        for (int i = 0; i < number_of_vertices; i++) {
            for (int j = 0; j < number_of_vertices; j++) {
                int edge_label;
                if (edge_label = rhs.get_edge(i, j, edge_label)) {
                    set_edge(i, edge_label, j);
                }
            }
        }
    }
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyMatrix::set_edge(int v1, int edge_label, int v2) {
    if (!has_edge(v1, v2)) {
        adj_matrix[index(v1, v2)] = new int;
        number_of_edges++;
    }
    *adj_matrix[index(v1, v2)] = edge_label;
}

// check if the given edge is in the graph
bool AdjacencyMatrix::has_edge(int v1, int v2) const {
    return adj_matrix[index(v1, v2)] != nullptr;
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyMatrix::get_edge(int v1, int v2, int& edge) const {
    if (!has_edge(v1, v2)) {
        return false;
    } else {
        edge = *adj_matrix[index(v1, v2)];
        return true;
    }
}

// remove edge between v1 and v2 if the edge exists
void AdjacencyMatrix::remove_edge(int v1, int v2) {
    if (has_edge(v1, v2)) {
        delete adj_matrix[index(v1, v2)];
        adj_matrix[index(v1, v2)] = nullptr;
        number_of_edges--;
    }
}

// get all vertices on an outgoing edge from given vertex
void AdjacencyMatrix::connected_to(int v1, std::list<int>& vertices) const {
    for (int i = 0; i < number_of_vertices; i++) {
        if (adj_matrix[index(v1, i)] != nullptr) {
            vertices.push_back(i);
        }
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyMatrix::connected_from(int v2, std::list<int>& vertices) const {
    for (int i = 0; i < number_of_vertices; i++) {
        if (adj_matrix[index(i, v2)] != nullptr) {
            vertices.push_back(i);
        }
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyMatrix::adjacent(int v, std::list<int>& vertices) const {
    std::list<int> vertices_from;
    std::list<int> vertices_to;
    connected_from(v, vertices_from);
    connected_to(v, vertices_to);
    vertices.insert(vertices.end(), vertices_from.begin(), vertices_from.end());
    vertices.insert(vertices.end(), vertices_to.begin(), vertices_to.end());
}

// get number of nodes in the graph
int AdjacencyMatrix::vertex_count() const {
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyMatrix::edge_count() const {
    return number_of_edges;
}

// return the matrix index for edge x->y
int AdjacencyMatrix::index(int x, int y) const {
    return number_of_vertices * x + y;
}

// delete the adjacency matrix
void AdjacencyMatrix::make_empty() {
    for (int i = 0; i < number_of_vertices * number_of_vertices; i++) {
        if (adj_matrix[i] != nullptr) {
            delete adj_matrix[i];
            adj_matrix[i] = nullptr;
        }
    }
    delete[] adj_matrix;
    adj_matrix = nullptr;
}