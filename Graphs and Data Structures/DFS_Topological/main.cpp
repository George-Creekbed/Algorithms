// computes minimum number of free cuts in a graph
// collapsed to 2 nodes through repeated, randomly
// chosen  contractions of edges
#include <iostream>
#include <vector>

//#include "Graph.h"
#include "DepthFirstSearch.h"

using std::cout;        using std::endl;
using std::vector;      using std::cin;

//extern int infinity;

int main(int argc, char** argv)     // argv[1] is 'topological_input'
{
    cout << "Reads graph input file ..." << endl;
// test for long file
//    Graph graph0(argv[1]);
//    graph0.output(1000);

// topological sorting for short file
    Graph graph0(argv[1], "short");
    graph0.output();

    cout << "Perform topological ordering of graph ...\n" << endl;
    Graph graph1 = topologicalSort(graph0);
    graph1.output();

    return 0;
}
