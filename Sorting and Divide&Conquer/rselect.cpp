// algorithm selects the required n-th statistic
// out an array of integers (the n-th element of the sorted array)
// with the help of randomised procedures
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>       // rand, srand
#include <ctime>         // time for srand
#include <utility>       // swap

using std::cout;         using std::endl;
using std::fstream;      using std::string;
using std::vector;       using std::stoi;
using std::swap;


void choosePivot(vector<int>::iterator& beg, vector<int>::iterator& end,
                                   vector<int>::iterator& pivot_position)
{
    ptrdiff_t range = end - beg;

    // randomised pivot position
    srand( time(NULL) );               // pick the seed

    int random_number = rand() % (range - 1);
    pivot_position = beg + random_number;
}


void partitionAroundPivot(vector<int>::iterator& beg, vector<int>::iterator& end,
                                            vector<int>::iterator& pivot_position)
{
    // swap pivot to the beginning of input array, if pivot is not already there
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


int rSelect(vector<int>::iterator& beg, vector<int>::iterator& end, const int target_position)
{
    // base case
    if (end - beg <= 1) return *beg;

    // choose pivot randomly
    vector<int>::iterator pivot_position;
    choosePivot(beg, end, pivot_position);  // returns the pivot_position at random

    vector<int>::iterator iterator_at_target_pos = beg + target_position;

    // partition data array around pivot
    partitionAroundPivot(beg, end, pivot_position);

    int target_minus_pivot = 0;
    for (vector<int>::iterator iter = beg; iter != pivot_position; iter++)
        --target_minus_pivot;
    if (-target_minus_pivot < target_position)  // this is: if (pivot - beg < target_position) ..
        target_minus_pivot += target_position - 1;
    else
        target_minus_pivot = 0;

    vector<int>::iterator after_pivot = pivot_position + 1;

    if (*pivot_position == *iterator_at_target_pos) return *pivot_position;
    else if (pivot_position > iterator_at_target_pos) return rSelect(beg, after_pivot, target_position);
    else return rSelect(after_pivot, end, target_minus_pivot);

    //return 0;           // it never gets here
}


// driver function extracts array median, but could be any other statistic
int main(int argc, char** argv)   // accepts name of text file as argument (without suffix '.txt')
{
    string tail(".txt");
    string filename(argv[1] + tail);
    fstream input(filename);

    cout << "Finding the i-th statistic out of elements in input file...\n";

    vector<int> data_array;     // this vector stores the numbers from file
    string string_element("");
    if (input) {
        while ( getline(input, string_element) ) {
            int element = stoi(string_element);
            data_array.push_back(element);
        }
    }
    input.close();

    vector<int>::iterator beg = data_array.begin();
    vector<int>::iterator end = data_array.end();

    vector<int>::size_type median_pos;
    if (data_array.size() % 2 == 0)     // even array size
        median_pos = data_array.size() / 2 - 1;
    else                                // odd array size
        median_pos = data_array.size() / 2;

    int median = rSelect(beg, end, median_pos);
  
    cout << "Median of given array of integers is: " << median << " at position " << median_pos << endl;

    return 0;
}
