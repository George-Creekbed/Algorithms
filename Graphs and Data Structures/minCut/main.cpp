// computes minimum number of free cuts in a graph
// collapsed to 2 nodes through repeated, randomly
// chosen  contractions of edges
#include <iostream>
#include <vector>
#include <cstdlib>       // rand, srand
#include <ctime>         // time for srand
#include <algorithm>     // find, min
#include <cmath>         // pow
#include "Graph.h"

using std::cout;        using std::endl;
using std::vector;      using std::find;
using std::pow;         using std::min;

int minCut(Graph& input)
{
    srand( time(NULL) );            // pick the seed
    // randomised node acting as first node of contracted edge
    int range_nodes = input.size();
    int random_node_position = rand() % (range_nodes - 1);
    int random_node = input[random_node_position].getLabel();  // random_node_position included 0 and excludes last node
    // pick second node of edge to contract from neighbours of random_node, named 'random_edge'
    int random_edge = 0;
    int range_edges = input[random_node_position].size();
    do {    // make sure random_edge is not the same as random_node
        int random_edge_in_node_edges = rand() % (range_edges - 1);
        random_edge = input[random_node_position].getEdge(random_edge_in_node_edges).getNodes()[1];
    } while (random_edge == random_node);

    // find 'random_edge' node position in graph
    int random_edge_position = 0;
    vector<Node>::iterator it_nodes = input.begin();
    while ( it_nodes != input.end() )
    {
        if (it_nodes->getLabel() == random_edge) {
            random_edge_position = it_nodes - input.begin();
            break;
        }
        it_nodes++;
    }

    // add edges of node 'random_edge'(second vertex of randomly contracted edge)
    // to 'random_node'(first end of contracted edge)
    input[random_node_position].insertEdges(input[random_edge_position].begin(), input[random_edge_position].end());
    // delete all self-loops in random_node
    for (vector<Edge>::iterator iter = input[random_node_position].begin();
                                iter != input[random_node_position].end(); ++iter)
    {
        if (iter->getNodes()[0] != random_node)    // turn first node of new edges to random_node
            iter->setNodes(random_node, iter->getNodes()[1]);
        if (iter->getNodes()[1] == random_edge)    // when second node of edges is random_edge, turn it to random_node
            iter->setNodes(iter->getNodes()[0], random_node);
        if (iter->getNodes()[0] == iter->getNodes()[1]) // erase selfloops edges, that now all (ranodm_node, random_node)
        {
            input[random_node_position].erase( iter - input[random_node_position].begin() );
            iter--; // indispensable, iter has been erased above
        }
    }
    // delete second node of contracted edge from the graph
    input.erase(random_edge_position);
    // modify other nodes in the graph that linked to second node 'random_edge'
    // to link to the first node of contraction, 'random_node', instead
    for (vector<Node>::iterator iter = input.begin(); iter != input.end(); ++iter)
    {
        Edge edge_to_rename(iter->getLabel(), random_edge);
        vector<Edge>::iterator rename_iter = iter->begin();
        while (rename_iter != iter->end())
        {
            rename_iter = find(iter->begin(), iter->end(), edge_to_rename);
            if (rename_iter != iter->end())
                rename_iter->setNodes(iter->getLabel(), random_node);
        }
    }

    return input[random_node_position].size();
}


int main(int argc, char** argv)     // argv[1] is 'karger_input'
{
    cout << "Reads graph input file..." << endl;
    Graph graph0(argv[1]);
    cout << "Outputs Graph: " << endl;
    //graph0.output();

    int minimum_cut = 100;
    int current_mincut;
    int number_of_trials = 0;
    const int NUM_ITERATIONS_MAX = (int) graph0.size(); // pow(graph0.size(), 2); // should be size^2*log(size)
    while (number_of_trials != NUM_ITERATIONS_MAX)
    {
        Graph graph1(graph0);
        while (graph1.size() > 2)
        {
            current_mincut = minCut(graph1);
        }
        number_of_trials++;
        minimum_cut = min(minimum_cut, current_mincut);
        cout << "Trial " << number_of_trials << ", free edges: "
                         << current_mincut << " and " << graph1[1].size() << endl;
    }

    //graph0.output();
    cout << endl;
    cout << "minimum cut is " << minimum_cut << ", after "
                              << number_of_trials << " trials.\n" << endl;

    return 0;
}
