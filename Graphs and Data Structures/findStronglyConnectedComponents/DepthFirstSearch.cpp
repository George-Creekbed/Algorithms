// Breadth-First Search implementation
// runs through a Graph
#ifndef DEPTHFIRSTSEARCH_CPP_INCLUDED
#define DEPTHFIRSTSEARCH_CPP_INCLUDED

#include <iostream>
#include <stack>
#include <vector>
#include "DepthFirstSearch.h"

using std::cout;    using std::endl;
using std::vector;  using std::stack;

// define type for explored/unexplored Nodes
// enum is_visited {not_visited, visited};

void recursivePartDFS(const Graph& G, const int node_label, vector<is_visited>& node_is_visited,
                      int& current_label, vector<int>& weights, stack<Node>& Q)
{
    Node current_node = Q.top();
    node_is_visited[node_label] = visited;

    // cout << "node: " << node_label + 1 << " weight: " << current_label + 1 << endl;    // debug
    Node linked_node;       // variable hosting node on other end
    for (size_t i = 0; i != current_node.size(); ++i) {     // explore nodes linked to current_node by an edge
        int linked_node_label = current_node.getEdge(i).getNodes()[1] - 1;  // '-1' important, C++ starts lists from 0
        linked_node = G.getNode(linked_node_label);

        if (node_is_visited[linked_node_label] == not_visited) {    // check if linked_node is already in the stack
            Q.push(linked_node);                                    // if not, add it to the stack
            recursivePartDFS(G, linked_node_label, node_is_visited, current_label, weights, Q);
            weights[linked_node_label] = current_label;
            --current_label;
        }
    }
    Q.pop();
}


void depthFirstSearch(const Graph& G, const int node_label, vector<is_visited>& node_is_visited,
                      int& current_label, vector<int>& weights)
{
    // this is the stack structure powering DFS
    stack<Node> Q;
    Node next_node = G.getNode(node_label);
    Q.push(next_node);

    // DFS algorithm
    while (Q.size() != 0) {     // out of main loop if all nodes searched->means no path is present
        recursivePartDFS(G, node_label, node_is_visited, current_label, weights, Q);
        weights[node_label] = current_label;
        --current_label;
    }
}


Graph topologicalSort(const Graph& G)
{
    // initialise auxiliary vectors
    vector<is_visited> node_is_visited(G.size(), not_visited);
    vector<int> weights( G.size() ); // topological order
    int current_label = G.size();    // initialised to total number of nodes, holds topological order

    // perform DFS, assign weights to Nodes
    for (size_t i = 0; i != G.size(); ++i) {   // loop over all nodes in G
        if (node_is_visited[i] == not_visited)
            depthFirstSearch(G, i, node_is_visited, current_label, weights);
    }

    // rename Nodes by topological order
    Graph ret;
//    for (size_t i = 0; i != G.size(); ++i)        // debug
//        cout << " weights " << weights[i] << " ";
//    cout << endl;
    for (size_t i = 0; i != G.size(); ++i) {
        Node node_i;
        node_i.setLabel(weights[i]);
        for (size_t j = 0; j != G.getNode(i).size(); ++j) {
            int end_node_in_edge_j = G.getNode(i).getEdge(j).getNodes()[1];
            Edge edge_j(weights[i], weights[end_node_in_edge_j - 1]);
            node_i.addEdge(edge_j);
        }
        ret.addNode(node_i);
    }

    return ret;
}

#endif // DEPTHFIRSTSEARCH_CPP_INCLUDED
