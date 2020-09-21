// Breadth-First Search implementation
// runs through a Graph
#ifndef BREADTHFIRSTSEARCH_CPP_INCLUDED
#define BREADTHFIRSTSEARCH_CPP_INCLUDED

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include "BreadthFirstSearch.h"

using std::cout;    using std::endl;
using std::cin;     using std::find_if;
using std::vector;  using std::queue;
using std::map;

bool breadthFirstSearch(const Graph& G, const int start_node_label, const int target_node_label)
{
    // define type for explored/unexplored Nodes
    enum is_visited {not_visited, visited};
    // initialise path length and node vectors
    //vector<int> dist(G_tot.size(), infinity);
    //vector<is_visited> node_is_visited(G_tot.size(), not_visited);
    map<int, is_visited> node_is_visited;
    for (Graph::const_iterator iter = G.begin(); iter != G.end(); ++iter)
        node_is_visited[iter->getLabel()] = not_visited;

    Graph::const_iterator start_node_iter =
                         find_if(G.begin(), G.end(), [=](const Node& i){return i.getLabel() == start_node_label;});
    // breadth-first algorithm runs based on following queue structure
    if ( start_node_iter == G.end() )
        return false;
    node_is_visited[start_node_label] = visited;

    Node next_node;
    next_node = *start_node_iter;

    queue<Node> Q;
    Q.push(next_node);
    // BFS algorithm
    while (Q.size() != 0) {     // out of main loop if all nodes searched->means no path is present
        Node current_node = Q.front();
        Node linked_node;       // variable hosting node on other end
        for (size_t i = 0; i != current_node.size(); ++i) {     // explore nodes linked to current_node by an edge
            int linked_node_label = current_node.getEdge(i).getNodes()[1];
            Graph::const_iterator is_linked_node_in_G =
                           find_if(G.begin(), G.end(), [=](const Node& a){return a.getLabel() == linked_node_label;});
            if ( is_linked_node_in_G != G.end() ) {    // check linked_node is in G
                linked_node = *is_linked_node_in_G; //G_tot.getNode(linked_node_label - 1);
                if (node_is_visited[linked_node_label] == not_visited) {    // check if linked_node is already in the queue
                    node_is_visited[linked_node_label] = visited;
                    Q.push(linked_node);                                    // if not, add it to the queue
                   // dist[linked_node_label - 1] = dist[current_node.getLabel() - 1] + 1;    // and update its path length
//                    cout << "current " << current_node.getLabel()       // for debug
//                         << " | linked = " << linked_node_label + 1
//                         << " | path length = " << dist[linked_node_label] << endl;
                    if (linked_node_label == target_node_label)  // end search once target node is explored
                        return true;
                }
            } else {
                if (linked_node_label == target_node_label)  // end search once target node is explored
                    return false;
            }
        }
        //if (linked_node.getLabel() == target_node_label) break;  // same, exit the outer loop
        Q.pop();
    }

    return false;
}

#endif // BREADTHFIRSTSEARCH_CPP_INCLUDED
