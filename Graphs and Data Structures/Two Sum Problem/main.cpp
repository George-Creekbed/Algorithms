/* Implementation of 2-Sum problem.
The file "homework_input.txt" contains n integers (n <= 1 million),
both positive and negative, with repetitions.
The i-th row of the file specifies the i-th entry of the array.
The program computes the number of target values t in the interval [-10000,10000]
such that there are distinct numbers x,y in the input file that satisfy x + y = t. */
#include <iostream>
#include <unordered_set>    // hash tables with just keys (unordered_map for pairs <key, value>)
#include <fstream>
#include <string>

using std::cout;            using std::endl;
using std::ifstream;        using std::string;
using std::unordered_set;

int main(int argc, char** argv)     // input filename: homework_input.txt
{
    cout << "Two-sums problem: " << endl;

    string filename = argv[1];
    filename += ".txt";
    ifstream is;
    is.open(filename);

    // fill hash table with input dataset
    unordered_set<long long> hash_table;
    while( !is.eof() )
    {
        long long current;
        is >> current;
        hash_table.insert(current);
    }
    is.close();

    cout << "Elements in the dataset: " << hash_table.size() << endl;
    cout << endl;

    // look for t - input[i] , t \in [-10000, 10000]
    long long total_complements(0);
    for (long long t = -10000; t != 10000; t++) {
        for (unordered_set<long long>::iterator iter = hash_table.begin();
                                          iter != hash_table.end(); iter++) {
            long long complement_iter_in_t = t - *iter;
            if (hash_table.find(complement_iter_in_t) != hash_table.end() && *iter != complement_iter_in_t) {
                total_complements++;
                break;
            }
        }
    }

    cout << "There are " << total_complements << " complements of [-10000, 10000] found in the dataset." << endl;

    return 0;
}
