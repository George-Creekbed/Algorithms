/* A max-spacing k-clustering program based on Kruskal MST algorithm.
The input file lists a complete graph with edge costs.
clusters k = 4 assumed.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>        // std::sort;
#include "computeHammingDist.h"
#include "DisjointSet.h"

using std::cout;                using std::endl;
using std::string;              using std::ifstream;
using std::vector;              using std::sort;
using std::unordered_multimap;  using std::tuple;
using std::tie;

int main(int argc, char** argv)
{
    cout << "Reading list of edges from input file ...\n" << endl;

    // read input file
    string filename(argv[1]);
    ifstream is(filename + ".txt");
    unordered_multimap<string, int> hash_to_labels;
    unordered_multimap<int, vector<int> > hash_to_bits;
    tie(hash_to_labels, hash_to_bits) = inputInHashTable(is);

    //outputHashTables(hash_to_labels, hash_to_bits);

    // initialise union-find structure and number of clusters to be equal to the number of nodes in input
    DisjointSet disjoint_set( hash_to_labels.size() );
    int number_of_clusters( hash_to_labels.size() );

    // check for Hamming distance = 0 (repeated nodes in input)
    number_of_clusters = mergeRepeatedNodes(number_of_clusters, hash_to_labels, disjoint_set);
    cout << "FINISH0\n";

    unordered_multimap<string, int> hash_to_nodes;  // hash table hosting permutations (=1 or 2) for current node 'i'
    vector<string> permutations;                    // array of permutations for node 'i'

    // check for Hamming distance = 1 (1 permutation)
    for (size_t i = 1; i <= hash_to_labels.size(); i++) {
        hash_to_nodes.clear();
        permutations = createPermutations1(hash_to_bits, hash_to_nodes, i);//hash_to_nodes);
        number_of_clusters = computeHammingDist(permutations, hash_to_labels, hash_to_nodes,
                                                disjoint_set, number_of_clusters);
    }
    cout << "FINISH1\n";

    // check for Hamming distance = 2 (2 permutations)
    for (size_t i = 1; i <= hash_to_labels.size(); i++) {
        hash_to_nodes.clear();
        permutations = createPermutations2(hash_to_bits, hash_to_nodes, i);
        number_of_clusters = computeHammingDist(permutations, hash_to_labels, hash_to_nodes,
                                                disjoint_set, number_of_clusters);
    }
    cout << "FINISH2\n";

    cout << "Number of clusters with Hamming distance equal or less than 2: " << number_of_clusters << '\n';
    cout << endl;

return 0;
}
