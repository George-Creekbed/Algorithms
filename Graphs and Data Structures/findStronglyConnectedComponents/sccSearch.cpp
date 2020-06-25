#ifndef SCCSEARCH_CPP_INCLUDED
#define SCCSEARCH_CPP_INCLUDED

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include "sccSearch.h"

using std::cout;    using std::endl;
using std::vector;  using std::stack;
using std::sort;

// define type for explored/unexplored Nodes
// enum is_visited {not_visited, visited};

// global counters
static int t;   // track node weights in first pass
static int current_root_label;  // current leader node label for 2nd pass

// sorts in decreasing order
bool compare(const int a, const int b)
{
    return a > b;
}

// depth first search algorithm, recursive bit
void recursivePartDFS(const Graph& G, const int current_node_label, vector<is_visited>& node_is_visited,
                      vector<int>& weights, vector<int>& leaders, stack<Node>& Q)
{
    Node current_node = Q.top();
    node_is_visited[current_node_label] = visited;
    leaders[current_node_label] = current_root_label;

    Node linked_node;       // variable hosting node on other end
    for (size_t i = 0; i != current_node.size(); ++i) {     // explore nodes linked to current_node by an edge
        int linked_node_label = current_node.getEdge(i).getNodes()[1] - 1;  // '-1' important, C++ starts lists from 0
        linked_node = G.getNode(linked_node_label);

        if (node_is_visited[linked_node_label] == not_visited) {    // check if linked_node is already in the stack
            Q.push(linked_node);                                    // if not, add it to the stack
            recursivePartDFS(G, linked_node_label, node_is_visited, weights, leaders, Q);   // recursion
            ++t;        // increment static once sink node is reached -> new weight, line below
            weights[linked_node_label] = t;
        }
    }
    Q.pop();
}

// depth first search algorithm
void depthFirstSearch(const Graph& G, const int current_node_label, vector<is_visited>& node_is_visited,
                      vector<int>& weights, vector<int>& leaders)
{
    stack<Node> Q;  // this is the stack structure powering DFS
    Node next_node = G.getNode(current_node_label);
    Q.push(next_node);

    // DFS algorithm
    while (Q.size() != 0) {     // out of main loop if all nodes searched -> means no path is present
        recursivePartDFS(G, current_node_label, node_is_visited, weights, leaders, Q);
        ++t;        // increment static once sink node is reached -> new weight, line below
        weights[current_node_label] = t;
    }
}

// 2 passes, scc search algorithm
vector<int> sccSearch (const Graph& G, const int pass)
{
    t = 0;  // initialize static variable
    current_root_label = G.size();
    vector<is_visited> node_is_visited(G.size(), not_visited);
    vector<int> weights( G.size() );
    vector<int> leaders( G.size() );

    for (int i = G.size() - 1; i != -1; --i) {  // cycle through nodes starting from the last given in input
        if (node_is_visited[i] == not_visited) {
            current_root_label = G.getNode(i).getLabel();
            depthFirstSearch(G, i, node_is_visited, weights, leaders);  // call DFS algorithm
        }
    }

    switch(pass) {
        case 1: return weights; break;  // 1st pass, assign order of visiting according to "weights"
        case 2: return leaders; break;  // 2nd pass, identify SCCs, each with their leader node
        default: cout << "Only values of 1 or 2 accepted as parameters" << endl;
    }

    return weights;   // never gets here
}

// reverses edge directions in directed Graph
Graph reverseGraph(const Graph& G)
{
    Graph ret;
    ret.reserve( G.size() );
    for (size_t i = 1; i != G.size() + 1; ++i) {    // initialise reversed Graph
        Node node;
        node.setLabel(i);
        ret.addNode(node);
    }
    //ret.output();     // debug

    int tail_node, end_node;
    for (size_t i = 0; i != G.size(); ++i) {        // reverse input Graph
        Node current_node;
        tail_node = G.getNode(i).getLabel();

        for (size_t j = 0; j != G.getNode(i).size(); ++j) {
            Edge current_edge;
            end_node = G.getNode(i).getEdge(j).getNodes()[1];
            current_edge.setNodes(end_node, tail_node);
            ret[end_node - 1].addEdge(current_edge);        // -1 important, end_node starts from 1, not 0
        }
    }

    return ret;
}

// main program
void driverProgram(const Graph& G, vector<int>& weights, vector<int>& leaders)
{
    cout << "Inverting edges in input Graph...\n" << endl;
    Graph G_rev = reverseGraph(G);
//    G_rev.output();       // debug

    // 1st pass: determine weights to each node in reversed Graph
    int pass(1);
    cout << "Assigning weights to nodes...\n" << endl;
    weights = sccSearch(G_rev, pass);
//    for (size_t i = 0; i != G.size(); ++i)        // debug
//        cout << "weights: " << i + 1 << " " << weights[i] << endl;

    // create new Graph from input and sort it according to weights
    Graph G_weights;
    G_weights.reserve( G.size() );
    for (size_t i = 0; i != G.size(); ++i) {
        G_weights.addNode( G.getNode(i) );
        G_weights[i].setLabel(weights[i]);
        for (size_t j = 0; j != G.getNode(i).size(); ++j) {
            int end_node = G.getNode(i).getEdge(j).getNodes()[1];
            G_weights[i].modifEdge(j).setNodes(weights[i], weights[end_node - 1]);
        }
    }
    sort(G_weights.begin(), G_weights.end(), compareNodes);

//    cout << endl;                    // debug
//    cout << "G_weights: " << endl;
//    G_weights.output();

    // 2nd pass: determine SCCs by assigning leader nodes to each SCC
    pass = 2;
    cout << "Assigning leaders to SCCs..." << endl;
    leaders = sccSearch(G_weights, pass);
    sort( leaders.begin(), leaders.end() );

    vector<int> leaders_counter;
    vector<int> scc_sizes;
    scc_sizes.reserve(800000);
    int counter_i(0);
    for (size_t i = 0; i != leaders.size(); ++i) {
        ++counter_i;
        if (leaders[i] != leaders[i+1]) {
            leaders_counter.push_back(leaders[i]);
            scc_sizes.push_back(counter_i);
            counter_i = 0;
        }
    }
    cout << endl;
    cout << "There are " << leaders_counter.size() << " strongly connected components (SCCs) in the graph." << endl;
//    cout << "'Leader' node of scc | scc size: " << endl;      // debug
//    vector<int> scc_sizes;
//    scc_sizes.reserve(900000);
//    for (size_t i = 0; i != leaders_counter.size(); ++i) {
//        int counter_i = count(leaders.begin(), leaders.end(), leaders_counter[i]);
//        cout << leaders_counter[i] << " | " << counter_i << endl;
//        scc_sizes.push_back(counter_i);
//    }

    // output size of the biggest 6 SCCs
    sort(scc_sizes.begin(), scc_sizes.end(), compare);
    cout << endl;
    cout << "The larger strongly connected components have sizes: ";
    for (int i = 0; i != 5; ++i) {
        if (scc_sizes[i])
            cout << scc_sizes[i] << " ";
        else
            cout << 0 << " ";
    }
    if (scc_sizes[5])
            cout << scc_sizes[5] << endl;
        else
            cout << endl;
    cout << endl;
}

#endif // SCCSEARCH_CPP_INCLUDED
