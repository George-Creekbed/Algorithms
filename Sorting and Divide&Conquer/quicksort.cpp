/* implementation of quicksort algorithm
sorts input file and outputs number of comparisons
Four versions: always first element as pivot,
always last element as pivot,
median between (first, middle, last) element as pivot,
completely randomised */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>     // sort
#include <utility>       // swap
#include <cstdlib>       // rand, srand
#include <ctime>         // time for srand

using std::cout;         using std::endl;
using std::fstream;      using std::string;
using std::vector;       using std::stoi;
using std::swap;         using std::sort;


void choosePivot(vector<int>::iterator& beg, vector<int>::iterator& end,
                                   vector<int>::iterator& pivot_position)
{
    ptrdiff_t range = end - beg;

    // first element as pivot
//    pivot_position = beg;

    // last element as pivot
//    pivot_position = end - 1;

    // min between first, last, and median position element as pivot
//    pivot_position = beg;
//
//    if (range == 2) {
//        return;
//    }
//
//    int median;
//    if ( range % 2 == 1) median = (range / 2) + 1;
//    else median = range / 2;
//
//    vector<int> sel_input = {*beg, *(beg + median - 1), *(end - 1)};
//
//    sort( sel_input.begin(), sel_input.end() );
//    vector<int>::iterator sel_position = sel_input.begin() + 1;
//    for (vector<int>::iterator jter = beg; jter != end; ++jter) {
//        if (*jter == *sel_position) {
//            pivot_position = jter;
//            break;
//        }
//    }

    // randomised pivot position
    srand( time(NULL) );                        // pick the seed
    pivot_position = beg + rand() % range;
}


void partitionAroundPivot(vector<int>::iterator& beg, vector<int>::iterator& end,
                                            vector<int>::iterator& pivot_position)
{
    // swap pivot to the beginning of input array
    if (beg != pivot_position) swap(*beg, *pivot_position);

    size_t i = 1;
    for (vector<int>::iterator jter = beg; jter != end; ++jter) {
        if (*jter < *beg) {
            swap(*(beg + i), *jter);
            ++i;
        }
    }
    swap( *beg, *(beg + i - 1) );   // set pivot sorted position
    pivot_position = beg + i - 1;   // reset pivot position so partition will be done correctly
}


// main sorting routine, outputs number of operations to gauge performance
int quickSort(vector<int>::iterator& beg, vector<int>::iterator& end)
{
    vector<int>::size_type size = end - beg;

    if (size < 2) return 0;

    static int count_comparisons = 0;

    vector<int>::iterator pivot_position;
    choosePivot(beg, end, pivot_position);

    partitionAroundPivot(beg, end, pivot_position);
    count_comparisons += size - 1;

    vector<int>::iterator after_pivot;
    pivot_position == end - 1 ? after_pivot = pivot_position : after_pivot = pivot_position + 1;
    if (size > 1) {
    }

    quickSort(beg, after_pivot);
    quickSort(after_pivot, end);

    return count_comparisons;
}


int main(int argc, char** argv)
{
    string tail(".txt");
    string filename(argv[1] + tail);
    fstream input(filename); //, fstream::in | fstream::out);

    cout << "Sorting the input file...\n";

    vector<int> data_array;
    string string_element("");
    if (input) {
        while ( getline(input, string_element) ) {
            int element = stoi(string_element);
            data_array.push_back(element);
        }
    }
    input.close();

    int comparisons;
    vector<int>::iterator beg = data_array.begin();
    vector<int>::iterator end = data_array.end();
    comparisons = quickSort(beg, end);

    input.open(filename, fstream::out | fstream::trunc);

    cout << "Sorted input array: " << endl;
    for (vector<int>::iterator iter = data_array.begin(); iter != data_array.end(); ++iter)
        input << *iter << endl;

    cout << "Number of comparisons: " << comparisons << endl;

    input.close();

    return 0;
}
