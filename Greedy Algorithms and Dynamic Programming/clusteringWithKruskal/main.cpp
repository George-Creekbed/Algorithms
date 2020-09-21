/* A max-spacing k-clustering program based on Kruskal MST algorithm.
The input file lists a complete graph with edge costs.
clusters k = 4 assumed.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>        // std::sort;
#include "Graph.h"
#include "KruskalClustering.h"

using std::cout;                using std::endl;
using std::string;              using std::ifstream;
using std::vector;              using std::sort;

int main(int argc, char** argv)
{
    cout << "Reading list of edges from input file ...\n" << endl;

    // read graph0 from input file
    string filename(argv[1]);

    Graph graph0(filename);
//    graph0.output();   // debug
    cout << endl;

    // re-read input file and create a list of all edges in graph0
    ifstream is(filename + ".txt");
    int nodes_size;
    is >> nodes_size;
    vector<Edge> edges;
    int node1, node2, cost;

    while (is >> node1 >> node2 >> cost) {
        Edge current_edge(node1, node2, cost);
        edges.push_back(current_edge);
    }
    is.close();

    // sort the edge list by increasing cost
    cout << "Sorting edges ...\n" << endl;
    sort(edges.begin(), edges.end(), compareCosts);
//    for (vector<Edge>::iterator iter = edges.begin(); iter != edges.end(); ++iter)       // debug
//        cout << (*iter).getNodes()[0] << " " << (*iter).getNodes()[1] << "  " << (*iter).getCost() << endl;

    cout << "Kruskal algorithm: Computing minimal distance between clusters when they are reduced to 4 ...\n" << endl;

    int k = 4;   // number of clusters desired

    // pick implementation, comment the other
    int clustering_min_dist = clusteringKruskalNaive(graph0, edges, k);
    //int clustering_min_dist = clusteringKruskalDisjointSet(graph0, edges, k);

    cout << "k = " << k << " clusters minimal distance is: " << clustering_min_dist << endl;

    return 0;
}
