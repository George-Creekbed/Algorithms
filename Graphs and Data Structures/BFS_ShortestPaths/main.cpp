// computes minimum number of free cuts in a graph
// collapsed to 2 nodes through repeated, randomly
// chosen  contractions of edges
#include <iostream>
#include <vector>
#include <limits>
//#include "Graph.h"
#include "BreadthFirstSearch.h"

using std::cout;        using std::endl;
using std::vector;      using std::cin;

extern int infinity;

int main(int argc, char** argv)     // argv[1] is 'karger_input'
{
    cout << "Reads graph input file..." << endl;
    Graph graph0(argv[1]);
    int starting_node, target_node;
    cout << "Insert starting node out of [0 - 200]: ";
    cin >> starting_node;
    cout << endl;
    cout << "Now insert target node: ";
    cin >> target_node;
    cout << endl;
    cout << "Computing shortest path length from node " << starting_node
         << " to node " << target_node << " ..." << endl;
    cout << endl;

    int min_path = breadthFirstSearch(graph0, starting_node - 1, target_node - 1);
    cout << endl;
    if (starting_node < 1 || target_node > 200 || min_path == infinity)
        cout << "No path is present\n" << endl;
    else
        cout << "Shortest path is " << min_path << " nodes long.\n" << endl;

    return 0;
}
