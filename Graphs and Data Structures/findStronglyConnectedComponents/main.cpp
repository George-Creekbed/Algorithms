// computes strongly connected components (SCC)
// out of an input Graph
// [need to increase stack memory size by using
// -Wl,--stack,1000000000
// in Settings -> compiler -> linker settings -> other linker options]
#include <iostream>
#include <vector>
#include "sccSearch.h"

using std::cout;        using std::endl;
using std::vector;

//extern int infinity;

int main(int argc, char** argv)     // argv[1] is 'scc_input'
{
    cout << "Reads graph input file ...\n" << endl;
// test for long file
    // read input
    Graph graph0(argv[1]);
//    graph0.output();      // debug

    vector<int> leaders( graph0.size() );
    vector<int> weights( graph0.size() );

    driverProgram(graph0, weights, leaders);

    return 0;
}
