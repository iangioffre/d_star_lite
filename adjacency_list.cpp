//----------------------------------------------------------------------
// NAME: Ian Gioffre
// FILE: adjacency_list.cpp
// DATE: Spring 2021
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#include "adjacency_list.h"

#include <iostream>

// default constructor
AdjacencyList::AdjacencyList(int vertex_count) {
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    adj_list_in = new Node*[vertex_count];
    adj_list_out = new Node*[vertex_count];
    for (int i = 0; i < vertex_count; i++) {
        adj_list_in[i] = nullptr;
        adj_list_out[i] = nullptr;
    }
}

// destructor
AdjacencyList::~AdjacencyList() {
    make_empty();
}

// copy constructor
AdjacencyList::AdjacencyList(const AdjacencyList& rhs) {
    number_of_vertices = 0;
    number_of_edges = 0;
    adj_list_out = nullptr;
    adj_list_in = nullptr;
    *this = rhs;
}

// assignment operator
AdjacencyList& AdjacencyList::operator=(const AdjacencyList& rhs) {
    if (this != &rhs) {
        make_empty();
        number_of_vertices = rhs.number_of_vertices;
        adj_list_out = new Node*[number_of_vertices];
        adj_list_in = new Node*[number_of_vertices];
        for (int i = 0; i < number_of_vertices; i++) {
            adj_list_in[i] = nullptr;
            adj_list_out[i] = nullptr;
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
void AdjacencyList::set_edge(int v1, int edge_label, int v2) {
    Node* currNode = nullptr;
    Node* prevNode = nullptr;
    if (!has_edge(v1, v2)) {
        // set out edge
        currNode = adj_list_out[v1];
        prevNode = nullptr;

        if (currNode == nullptr) {
            // no nodes in the chain
            adj_list_out[v1] = new Node();
            adj_list_out[v1]->vertex = v2;
            adj_list_out[v1]->edge = edge_label;
            adj_list_out[v1]->next = nullptr;
        } else {
            while(currNode != nullptr) {
                prevNode = currNode;
                currNode = currNode->next;
            }
            currNode = new Node();
            currNode->vertex = v2;
            currNode->edge = edge_label;
            currNode->next = nullptr;
            prevNode->next = currNode;
        }

        // set in edge
        currNode = adj_list_in[v2];
        prevNode = nullptr;
        if (currNode == nullptr) {
            // no nodes in the chain
            adj_list_in[v2] = new Node();
            adj_list_in[v2]->vertex = v1;
            adj_list_in[v2]->edge = edge_label;
            adj_list_in[v2]->next = nullptr;
        } else {
            while(currNode != nullptr) {
                prevNode = currNode;
                currNode = currNode->next;
            }
            currNode = new Node();
            currNode->vertex = v1;
            currNode->edge = edge_label;
            currNode->next = nullptr;
            prevNode->next = currNode;
        }

        number_of_edges++;
    } else {
        // set out edge
        currNode = adj_list_out[v1];
        while(currNode->vertex != v1) {
            currNode = currNode->next;
        }
        currNode->edge = edge_label;

        // set in edge
        currNode = adj_list_in[v2];
        while(currNode->vertex != v2) {
            currNode = currNode->next;
        }
        currNode->edge = edge_label;
    }
}

// check if the given edge is in the graph
bool AdjacencyList::has_edge(int v1, int v2) const {
    Node* currNode = adj_list_out[v1];
    while (currNode != nullptr) {
        if (currNode->vertex == v2) {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyList::get_edge(int v1, int v2, int& edge) const {
    if (!has_edge(v1, v2)) {
        return false;
    } else {
        Node* currNode = adj_list_out[v1];
        while(currNode != nullptr && currNode->vertex != v2) {
            currNode = currNode->next;
        }
        edge = currNode->edge;
        return true;
    }
}

// remove edge between v1 and v2 if the edge exists
void AdjacencyList::remove_edge(int v1, int v2) {
    Node* currNode = adj_list_out[v1];
    Node* prevNode = nullptr;
    bool nodeNotFound = true;
    while (currNode != nullptr && nodeNotFound) {
        if (currNode->vertex == v2) {
            nodeNotFound = false;
            if (prevNode == nullptr) {
                adj_list_out[v1] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            delete currNode;
            currNode = nullptr;
        } else {
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    currNode = adj_list_in[v2];
    prevNode = nullptr;
    nodeNotFound = true;
    while (currNode != nullptr && nodeNotFound) {
        if (currNode->vertex == v1) {
            nodeNotFound = false;
            if (prevNode == nullptr) {
                adj_list_in[v2] = currNode->next;
            } else {
                prevNode->next = currNode->next;
            }
            delete currNode;
            currNode = nullptr;
        } else {
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
    
    if (!nodeNotFound) {
        number_of_edges--;
    }
}

// get all vertices on an outgoing edge from given vertex
void AdjacencyList::connected_to(int v1, std::list<int>& vertices) const {
    Node* currNode = adj_list_out[v1];
    while (currNode != nullptr) {
        vertices.push_back(currNode->vertex);
        currNode = currNode->next;
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyList::connected_from(int v2, std::list<int>& vertices) const {
    Node* currNode = adj_list_in[v2];
    while (currNode != nullptr) {
        vertices.push_back(currNode->vertex);
        currNode = currNode->next;
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyList::adjacent(int v, std::list<int>& vertices) const {
    std::list<int> vertices_from;
    std::list<int> vertices_to;
    connected_from(v, vertices_from);
    connected_to(v, vertices_to);
    vertices.insert(vertices.end(), vertices_from.begin(), vertices_from.end());
    vertices.insert(vertices.end(), vertices_to.begin(), vertices_to.end());
}

// get number of nodes in the graph
int AdjacencyList::vertex_count() const {
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyList::edge_count() const {
    return number_of_edges;
}

// helper function to delete adj_list
void AdjacencyList::make_empty() {
    // clear out list
    for (int i = 0; i < number_of_vertices; i++) {
        Node* currNode = adj_list_out[i];
        Node* nextNode = nullptr;
        while (currNode != nullptr) {
            nextNode = currNode->next;
            delete currNode;
            currNode = nextNode;
        }
    }
    delete[] adj_list_out;
    adj_list_out = nullptr;

    // clear in list
    for (int i = 0; i < number_of_vertices; i++) {
        Node* currNode = adj_list_in[i];
        Node* nextNode = nullptr;
        while (currNode != nullptr) {
            nextNode = currNode->next;
            delete currNode;
            currNode = nextNode;
        }
    }
    delete[] adj_list_in;
    adj_list_in = nullptr;
}