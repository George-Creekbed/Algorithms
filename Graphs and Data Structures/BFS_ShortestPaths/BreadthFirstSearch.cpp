// Breadth-First Search implementation
// runs through a Graph
#ifndef BREADTHFIRSTSEARCH_CPP_INCLUDED
#define BREADTHFIRSTSEARCH_CPP_INCLUDED

#include <iostream>
#include <limits>
#include <queue>
#include <vector>
#include "BreadthFirstSearch.h"

using std::cout;    using std::endl;
using std::cin;     using std::numeric_limits;
using std::vector;  using std::queue;

int infinity = numeric_limits<int>::infinity();

int breadthFirstSearch(const Graph& G, const int start_node_label, const int target_node_label)
{
    // define type for explored/unexplored Nodes
    enum is_visited {not_visited, visited};
    // initialise path length and node vectors
    vector<int> dist(G.size(), infinity);
    vector<is_visited> node_is_visited(G.size(), not_visited);
    node_is_visited[start_node_label] = visited;

    // this is the queue structure on which the breadth-first algorithm runs
    queue<Node> Q;
    Node next_node = G.getNode(start_node_label);
    Q.push(next_node);

    // BFS algorithm
    while (Q.size() != 0) {     // out of main loop if all nodes searched->means no path is present
        Node current_node = Q.front();
        Node linked_node;       // variable hosting node on other end
        for (size_t i = 0; i != current_node.size(); ++i) {     // explore nodes linked to current_node by an edge
            int linked_node_label = current_node.getEdge(i).getNodes()[1] - 1;  // '-1' important, C++ starts lists from 0
            linked_node = G.getNode(linked_node_label);

            if (node_is_visited[linked_node_label] == not_visited) {    // check if linked_node is already in the queue
                node_is_visited[linked_node_label] = visited;
                Q.push(linked_node);                                    // if not, add it to the queue
                dist[linked_node_label] = dist[current_node.getLabel() - 1] + 1;    // and update its path length
//                cout << "current " << current_node.getLabel()       // for debug
//                     << " | linked = " << linked_node_label + 1
//                     << " | path length = " << dist[linked_node_label] << endl;
            }
            if (linked_node_label == target_node_label) break;  // end search once target node is explored
        }
        if (linked_node.getLabel() - 1 == target_node_label) break;  // same, exit the outer loop
        Q.pop();
    }

    return dist[target_node_label];
}

#endif // BREADTHFIRSTSEARCH_CPP_INCLUDED
