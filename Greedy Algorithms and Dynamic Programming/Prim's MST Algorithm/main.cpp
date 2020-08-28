// find Minimum Spanning Tree (MST) of a Graph using greedy Prim's algorithm.
// a) naive slower version just follows algorithm, complexity o(m*n),  ex: 0.234 s -- 538 s
// b) using a heap data structure hosting Nodes yet to be traversed lowers time
//    complexity to o( m*log(n) ) where m are #Edges and n the #Nodes, ex: 0.016 s -- 0.078 s :1 order of magnitude less
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>     // std::accumulate
#include <cstdlib>     // std::rand
#include <ctime>       // std::time
#include "Graph.h"

using namespace std;

const int INFTY = 10E8;


list<Edge> naivePrim(Graph& graph)
{
    list<Node> X;
    // initialise X
    srand( time(NULL) );    // initialize random seed
    int random_start = rand() % graph.size();   // random choice of starting Node
    X.push_back(graph[random_start]);
    list<Edge> T;
    list<Edge> cutting_edges;

    while ( X.size() != graph.size() ) {
        for (list<Node>::iterator iter = X.begin(); iter != X.end(); ++iter) {
            for (list<Edge>::iterator jter = (*iter).begin(); jter != (*iter).end(); ++jter) {
                if ( find_if(X.begin(), X.end(), [jter](Node i){return i.getLabel() == (*jter).getNodes()[1];}) == X.end() )
                    cutting_edges.push_back(*jter);
            }
        }

        list<Edge>::iterator iter_min_Edge = min_element(cutting_edges.begin(), cutting_edges.end(),
                                                         [](Edge& a, Edge& b){return a.getCost() < b.getCost();});

        X.push_back(graph[(*iter_min_Edge).getNodes()[1] - 1]);
        T.push_back(*iter_min_Edge);

        cutting_edges.clear();
    }

//    cout << "Nodes in X: ";
//    for (list<Node>::iterator iter = X.begin(); iter != X.end(); ++iter)
//        cout << (*iter).getLabel() << " ";
//    cout << endl;
//    cout << "evolution of minimum edges T: ";
//    for (list<Edge>::iterator iter = T.begin(); iter != T.end(); ++iter)
//        cout << (*iter).getNodes()[0] << "-" << (*iter).getNodes()[1] << "(" << (*iter).getCost() << ");  ";
//    cout << endl;

    return T;
}


list<Edge> heapPrim(Graph& graph)
{
    // initialise map to check if a node is in X
    bool (*pointer_to_compareLabels)(const Node&, const Node&) = compareLabels; // we need a pointer to function
    map<Node, bool, bool(*)(const Node&, const Node&)> is_in_X(*pointer_to_compareLabels); // awkward pointer definition
    for (Graph::iterator iter = graph.begin(); iter != graph.end(); iter++)
        is_in_X[*iter] = false;

    // initialise X
    srand( time(NULL) );    // initialize random seed
    int random_start = rand() % graph.size();   // random choice of starting Node
    list<Node> X(1, graph[random_start]);
    is_in_X[X.front()] = true;

    // initialise V - X (all nodes not in X)
    vector<Node> unexplored_nodes( graph.begin(), graph.end() );
    remove_if(unexplored_nodes.begin(), unexplored_nodes.end(),   // take node in X out of V - X
              [X](const Node& a){return a == X.front();});
    unexplored_nodes.pop_back();

    // iterate on Edges of lone element of X, adapt the cost of the Edge as the new score for neighbour
    for (Node::iterator iter_edge = X.front().begin(); iter_edge != X.front().end(); ++iter_edge) {
        vector<Node>::iterator neighbour_iter =        // neighbour Node on other side of each Edge of initial Node in X
                find_if(unexplored_nodes.begin(), unexplored_nodes.end(), [=](const Node& i) {
                    return i.getLabel() == (*iter_edge).getNodes()[1];
                });

        (*neighbour_iter).setScore( (*iter_edge).getCost() );   // set score of neighbour Node to the Edge cost

//        cout << "current_node_iter: " << (*neighbour_iter).getLabel() << " current edge "      // debug
//             << (*iter_edge).getNodes()[0] << "-" << (*iter_edge).getNodes()[1] << " edge cost: "
//             << (*iter_edge).getCost() << " while node score is " << (*neighbour_iter).getScore() << endl;
    }

    // initialise list of traversed Edges
    list<Edge> T;

    // main loop: traverses V-X and adds min Edge to T, and neighbour Node on other side of min Edge to X
    while ( X.size() != graph.size() ) {
        // transform V-X into a heap (top Node has min Score, other Nodes positions at random)
        make_heap(unexplored_nodes.begin(), unexplored_nodes.end(), compareScores);
        Node& top_heap = unexplored_nodes.front();

        // update scores of Nodes in V-X that are neighbours to top-heap Node, now in X
        for (Node::iterator iter = top_heap.begin(); iter != top_heap.end(); ++iter) {  // edges in Node front of V-X
            int current_node_label = (*iter).getNodes()[1];
            vector<Node>::iterator current_node_iter = find_if(unexplored_nodes.begin(), unexplored_nodes.end(),
                                                               [current_node_label](const Node& i) {
                                                                   return current_node_label == i.getLabel();
                                                       });
            if (!is_in_X[(*current_node_iter)]) {   // if neighbour not already in X, update its Score
                if ( current_node_iter != unexplored_nodes.end() )
                    (*current_node_iter).setScore( min( (*current_node_iter).getScore(), (*iter).getCost() ) );
            }
//            cout << "yes, current_node_iter: " << (*current_node_iter).getLabel() << " current edge "   // debug
//                 << (*iter).getNodes()[0] << "-" << (*iter).getNodes()[1] << " edge cost: "
//                 << (*iter).getCost() << " while node score is " << (*current_node_iter).getScore() << endl;
        }

        // push into X top node in V-X
        X.push_back(top_heap);
        is_in_X[top_heap] = true;   // update map of explored Nodes
        // push Edge with smallest cost in T
        Node::iterator smallest_edge_iter = find_if(top_heap.begin(), top_heap.end(),
                                            [=](const Edge& i){return i.getCost() == top_heap.getScore();});
        if ( smallest_edge_iter != top_heap.end() )
            T.push_back(*smallest_edge_iter);
//        cout << "top heap: " << top_heap.getLabel() << " smallest_edge: " << smallest_edge_iter->getNodes()[0] << "-"                // debug
//             << smallest_edge_iter->getNodes()[1] << " " << smallest_edge_iter->getCost() << endl;

        // remove top_heap from V-X
        pop_heap(unexplored_nodes.begin(), unexplored_nodes.end(), compareScores);
        unexplored_nodes.pop_back();
    }

//    cout << "evolution of new nodes X: ";   // debug
//    for (list<Node>::iterator iter = X.begin(); iter != X.end(); ++iter)
//        cout << (*iter).getLabel() << ";  ";
//    cout << endl;
//
//    cout << "evolution of minimum edges T: ";
//    for (list<Edge>::iterator iter = T.begin(); iter != T.end(); ++iter)
//        cout << (*iter).getNodes()[0] << "-" << (*iter).getNodes()[1] << "(" << (*iter).getCost() << ");  ";
//    cout << endl;

    return T;
}


int main(int argc, char** argv)         // input filename: 'edges'
{
    cout << "Reading Graph from input file ...\n" << endl;
    string filename(argv[1]);
    Graph graph0(filename);
//    graph0.output();

    //list<Edge> MST_Edges = naivePrim(graph0);
    list<Edge> MST_Edges = heapPrim(graph0);
    int sum_costs = accumulate(MST_Edges.begin(), MST_Edges.end(), 0,
                               [&](int sum, Edge b)->int {return sum + b.getCost();});

    cout << "The sum of costs of all edges in the MST is " << sum_costs << "." << endl;

    return 0;
}
