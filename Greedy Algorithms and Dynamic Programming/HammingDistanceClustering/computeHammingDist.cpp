/* Clustering on an input Graph where the distances (i.e., edge costs)
are only defined implicitly, rather than being provided as an explicit list.
For example, "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1",
24 bits associated with a node.
The distance between two nodes is defined as the Hamming distance
-- the number of differing bits -- between the two nodes' labels.
For example, the Hamming distance between the 24-bit label of node above
and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3
(since they differ in the 3rd, 7th, and 21st bits).
The question is: what is the largest value of k such that
there is a k-clustering with spacing at least 3?
That is, how many clusters are needed to ensure that no pair of nodes
with all but 2 bits in common get split into different clusters? */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>        // std::unordered_multimap (hash table allowing multiple entries with same key)
#include <vector>
#include <tuple>
#include <algorithm>            // std::for_each
#include <stdexcept>            // std::runtime_error
#include "computeHammingDist.h"
#include "split.h"

using std::cout;                   using std::endl;
using std::string;                 using std::istream;
using std::unordered_multimap;     using std::vector;
using std::stoi;                   using std::for_each;
using std::runtime_error;          using std::tuple;
using std::get;                    using std::tie;

// reads input file
tuple<unordered_multimap<string, int>, unordered_multimap< int, vector<int> > > inputInHashTable(istream& is)
{
    int number_nodes, number_bits;
    is >> number_nodes >> number_bits;

    string line;
    int node_index(1);
    getline(is, line);              // get first line
    unordered_multimap<string, int> hash_to_index;       // node bits as string, key to the node's number
    hash_to_index.reserve(number_nodes);
    unordered_multimap< int, vector<int> > hash_to_bits; // node bits as a <vector> of int
    hash_to_bits.reserve(number_nodes);

    // read nodes bits and create vector<int>s out of them
    while ( getline(is, line) ) {
        vector<string> bits_str = split(line);      // uses function split.h
        vector<int> bits;
        for_each(bits_str.begin(), bits_str.end(),
            [&](string& i) {
                bits.push_back( stoi(i) );
            });

        hash_to_index.insert({line, node_index});
        hash_to_bits.insert({node_index++, bits});
    }

    if ( !is.eof() )
        throw runtime_error("Something went wrong reading the input");

    tuple< unordered_multimap<string, int>, unordered_multimap< int, vector<int> > > ret(hash_to_index, hash_to_bits);

    return ret;
}


// flips bit 'i' in node
vector<int> permute1Bit(const vector<int>& input, const int index)
{
    vector<int> output(input);
    input[index] ? output[index] = 0 : output[index] = 1;

    return output;
}


// prints vector bits into a string again
string vectorToString(const vector<int>& input)
{
    string bits_string;
    for (auto j : input) {
        // remember, true = 1; false = 0
        j ? bits_string.append("1") : bits_string.append("0");
        bits_string.append(" ");
    }
    bits_string.pop_back();

    return bits_string;
}


// just lists again all nodes' bits without permutations (not used)
vector<string> createPermutations0(const unordered_multimap<int, vector<int> >& hash_to_bits,
                                  unordered_multimap<string, int>& hash_to_nodes)
{
    string bits_string;
    int counter( hash_to_bits.size() );
    vector<string> permutations;
    permutations.reserve( hash_to_nodes.size() );

    for (auto i : hash_to_bits) {                              // 0 permutations case
        bits_string = vectorToString(i.second);
        hash_to_nodes.insert({bits_string, counter});
        permutations.push_back(bits_string);
        counter--;
//        cout << "0 permutations: " << bits_string << '\n';
    }

    return permutations;
}


// creates all 1-bit permutations of 'current_node' and collates them into a vector
vector<string> createPermutations1(const unordered_multimap<int, vector<int> >& hash_to_bits,
                                  unordered_multimap<string, int>& hash_to_nodes, const int current_node)
{
    string bits_string;
    vector<string> permutations;
    permutations.reserve( hash_to_bits.size() );

    for (vector<int>::size_type j = 0; j != hash_to_bits.find(current_node)->second.size(); j++) {     // 1 permutations cases
        vector<int> permutation = permute1Bit(hash_to_bits.find(current_node)->second, j);
        bits_string = vectorToString(permutation);
        hash_to_nodes.insert({bits_string, current_node});
        permutations.push_back(bits_string);
//        cout << "1 permutations: " << bits_string << '\n';
    }

    return permutations;
}


// creates all 2-bit permutations of 'current_node' and collates them into a vector
vector<string> createPermutations2(const unordered_multimap<int, vector<int> >& hash_to_bits,
                                  unordered_multimap<string, int>& hash_to_nodes, const int current_node)
{
    string bits_string;
    vector<string> permutations;

    for (vector<int>::size_type j = 0; j != hash_to_bits.find(current_node)->second.size() - 1; j++) { // 2 permutations cases
        vector<int> permutation = permute1Bit(hash_to_bits.find(current_node)->second, j);
        for (vector<int>::size_type k = j + 1; k != permutation.size(); k++) {
            vector<int> second_permutation = permute1Bit(permutation, k);
            bits_string = vectorToString(second_permutation);
            hash_to_nodes.insert({bits_string, current_node});
            permutations.push_back(bits_string);
//            cout << "2 permutations: " << bits_string << '\n';
        }
    }

    return permutations;
}


// if any node is repeated in the input, merges their union-find structures
int mergeRepeatedNodes(const int initial_number_of_clusters, const unordered_multimap<string, int>& hash_to_labels,
                       DisjointSet& disjoint_set)
{
    int number_of_clusters = initial_number_of_clusters;
    for (auto i : hash_to_labels) {
        // Merge nodes in input that are repeated
        if (hash_to_labels.count(i.first) > 1){
            // equal_range collects all same-key entries in a multimap, in the form of iterators from .first to .second (last)
            auto equals = hash_to_labels.equal_range(i.first);
            for (auto iter = equals.first; iter != equals.second; iter++) {
                if ( disjoint_set.find(iter->second) !=
                    disjoint_set.find(hash_to_labels.equal_range(i.first).first->second) )
                {
                    disjoint_set.unionNodes( disjoint_set.find(iter->second),
                                            disjoint_set.find(hash_to_labels.equal_range(i.first).first->second) );
                    number_of_clusters--;
                }
            }
        }
    }

    return number_of_clusters;
}


// checks if nodes are at distance <= 2, merges union-find leaders if so, outputs final number of clusters remaining
int computeHammingDist(const vector<string>& permutation_list, const unordered_multimap<string, int>& hash_to_labels,
                       const unordered_multimap<string, int>& hash_to_nodes, DisjointSet& disjoint_set,
                       const int initial_number_of_clusters)
{
    // Start with every node being in its own cluster
    int number_of_clusters = initial_number_of_clusters;

    // Iterate over all permutations considered and determine number of clusters formed
    for (auto iter = permutation_list.begin(); iter != permutation_list.end(); ++iter) {
        string current_bits_string = *iter;
        unordered_multimap<string, int>::const_iterator bits_string_iter = hash_to_labels.find(current_bits_string);

        // Skip the edge if it is within a single cluster
        if ( bits_string_iter == hash_to_labels.end() )
            continue;

//        cout << "clusters: " << number_of_clusters << '\n';       // debug
////        cout << "disjoint set:\n";
//        for (size_t i = 0; i != disjoint_set.getSize(); i++)
//            cout << disjoint_set.get(i) << " ";
//        cout << endl;

        // Else, this edge joins two clusters
        if ( disjoint_set.find(hash_to_nodes.find(current_bits_string)->second) !=
            disjoint_set.find( (*bits_string_iter).second ) )
        {
            number_of_clusters--;
            disjoint_set.unionNodes(hash_to_nodes.find(current_bits_string)->second, (*bits_string_iter).second);
        }
    }

    return number_of_clusters;
}


// output multimaps, for debugging purposes
void outputHashTables(const unordered_multimap<string, int>& hash_to_labels,
                      const unordered_multimap<int, vector<int> >& hash_to_bits)
{
    cout << "List first hash table: code as string -> node int label:\n";
    for (unordered_multimap<string, int>::const_iterator iter = hash_to_labels.begin(); iter != hash_to_labels.end(); ++iter)
        cout << (*iter).first << " - " << (*iter).second << "\n";
    cout << endl;
    cout << "Now list second hash table: node int label -> code as vector of int:\n";
    for (unordered_multimap<int, vector<int> >::const_iterator iter = hash_to_bits.begin(); iter != hash_to_bits.end(); ++iter) {
        cout << (*iter).first << ": ";
        for (vector<int>::const_iterator jter = (*iter).second.begin(); jter != (*iter).second.end(); ++jter)
            cout << *jter << " ";
        cout << "\n";
    }
    cout << endl;
}
