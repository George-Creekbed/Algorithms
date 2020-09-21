// Kruskal MST algorithm. Implementation specific to  (k=4)-clustering
// -naive (with breadth-first-search to check whether new edge creates a cycle); cost: O(#_edges * #_nodes)
// -and union-find implementations.  Cost: O(#_edges*log2(#_nodes))
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>        //std::find_if
#include "BreadthFirstSearch.h"
#include "KruskalClustering.h"

using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::find_if;

int clusteringKruskalNaive(const Graph& graph0, const vector<Edge>& edges, int k)
{
    Graph T;    // Minimum Spanning Tree
    vector<Edge>::const_iterator edges_iter = edges.begin();
    int sum_costs(0), number_of_clusters( graph0.size() );  // keep track of overall cost of edges in T, and of clusters
    while (number_of_clusters >= k) {

        // find out if first node of edge is already in T
        Graph::iterator is1_in_T = find_if(T.begin(), T.end(),
                        [=] (Node& a) {return a.getLabel() == graph0.getNode(edges_iter->getNodes()[0] - 1).getLabel();});
        bool is1_in_T_flag;         // needed because T size is increased, and thus invalidates iterator is1_in_T
        Node* node_1 = new Node(*edges_iter); // no use of pointer here, it creates a new Node anyway, can't move Nodes to T
        if ( is1_in_T == T.end() ) {      // node_1 not in T so we add it
            T.addNode(*node_1);
            number_of_clusters--;         // node_1 is not its own cluster any more
            delete node_1;                // node_1 copied to T so ...
            node_1 = &(T[T.size() - 1]);  // ... it now points there
            sum_costs += (*edges_iter).getCost();
            is1_in_T_flag = false;
        } else {                          // node_1 is in T already
            delete node_1;                // if so, just update the pointer
            node_1 = &(*is1_in_T);
            is1_in_T_flag = true;
        }

        // perform BFS to check for cycles
        bool check_cycles = breadthFirstSearch(T, edges_iter->getNodes()[0], edges_iter->getNodes()[1]);

        // create an identical edge, but with nodes positions swapped
        Edge swapped_edge = *edges_iter;
        swapped_edge.swapNodes();
        // find out if second node of edge is already in T
        Graph::iterator is2_in_T = find_if( T.begin(), T.end(),
                        [=] (Node& a) {return a.getLabel() == graph0.getNode(edges_iter->getNodes()[1] - 1).getLabel();});
        // (either node1 or 2 not in T, or both, or both present but in different clusters of T)
        if (!check_cycles) {         // if edges_iter creates no cycle when added to T
            if (is1_in_T_flag){          // if node_1 was already present in T
                (*node_1).addEdge(*edges_iter);       // just add new edge to node_1 list of edges
                sum_costs += (*edges_iter).getCost();
            } else
                number_of_clusters++;   // if node_1 not present, it means number_of_cl was decreased above ...

            number_of_clusters--;       // ... and number_of_cl can decrease just by one, if adding an edge to T
            if ( is2_in_T != T.end() )  // node_2 already in T: just update its list of edges
                (*is2_in_T).addEdge(swapped_edge);
            else {                      // node_2 not in T, so add it
                Node node_2(swapped_edge);
                T.addNode(node_2);
            }

        } else {                        // cycle created by *edges_iter
            if (!is1_in_T_flag)         // in case the cycle happened just after adding node_1:
                (*is2_in_T).addEdge(swapped_edge);   // add edge to node_2, num_clusters already updated by node_1
        }
        if (number_of_clusters >= k)    // advance to next Edge if num_clusters > k
            edges_iter++;

        // debug
//        T.output();
//        cout << "next edge: (" << (*edges_iter).getNodes()[0] << "-"
//             << (*edges_iter).getNodes()[1] << ") " << endl;
//        cout << "clustering: " << number_of_clusters << endl;
        //cout << "current sum of edges: " << sum_costs << endl;
    }
    cout << "Sum of MST lengths is: " << sum_costs << endl;

    return (*edges_iter).getCost();
}


// same algorithm, implemented with Union-find structure
int clusteringKruskalDisjointSet(const Graph& graph0, const vector<Edge>& edges, int k)
{
    DisjointSet disjoint_set_graph0( graph0.size() );       // create Union-find structure

    Graph T;
    vector<Edge>::const_iterator edges_iter = edges.begin();
    int sum_costs(0), number_of_clusters( graph0.size() );

    while ( number_of_clusters >= k ) {
        // if nodes in Edge have not the same leader in the disjoint set, then no loop is created, and T can add the edge
        if ( disjoint_set_graph0.find(graph0.getNode(edges_iter->getNodes()[0] - 1)) !=
        disjoint_set_graph0.find(graph0.getNode(edges_iter->getNodes()[1] - 1)) ) {
            sum_costs += (*edges_iter).getCost();
            number_of_clusters--;               // no cycle created so the edge will be added to T

            // look for node_1 in T
            Graph::iterator is1_in_T = find_if(T.begin(), T.end(),
                        [=] (Node& a) {return a.getLabel() == graph0.getNode(edges_iter->getNodes()[0] - 1).getLabel();});
            if ( is1_in_T == T.end() ) {   // if node_1 not in T add it
                Node node1(*edges_iter);
                T.addNode(node1);
            } else                         // if node_1 already in T only add to it this edge
                (*is1_in_T).addEdge(*edges_iter);

            Edge swapped_edge = *edges_iter;
            swapped_edge.swapNodes();
            // look for node_2 in T
            Graph::iterator is2_in_T = find_if(T.begin(), T.end(),
                        [=] (Node& a) {return a.getLabel() == graph0.getNode(edges_iter->getNodes()[1] - 1).getLabel();});
            if ( is2_in_T == T.end() ) {     // same as for node_1
                Node node2(swapped_edge);
                T.addNode(node2);
            } else
                (*is2_in_T).addEdge(swapped_edge);

            // merge the 2 nodes' sets: update their disjointed set leaders
            disjoint_set_graph0.unionNodes( graph0.getNode(edges_iter->getNodes()[0] - 1),
                                           graph0.getNode(edges_iter->getNodes()[1] - 1) );
        }

        if (number_of_clusters >= 4)
            edges_iter++;
        //debug
//        T.output();
//        cout << "next edge: (" << (*edges_iter).getNodes()[0] << "-"
//             << (*edges_iter).getNodes()[1] << ") " << endl;
//        cout << "clustering: " << number_of_clusters << endl;
//        for (size_t i = 0; i != graph0.size(); ++i)
//            cout << disjoint_set_graph0.get(i) << " ";
//        cout << endl;
//        cout << "current sum of edges: " << sum_costs << endl;
    }
    cout << "Sum of MST lengths is: " << sum_costs << endl;

    return (*edges_iter).getCost();
}
