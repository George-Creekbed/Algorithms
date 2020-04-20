/* dSelect yields the selected statistic position in
   the input array without resorting to random procedures
   but still maintaining the o(n) cost of rSelect */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>       // rand, srand
#include <ctime>         // time for srand
#include <utility>       // swap
#include <algorithm>

using std::cout;         using std::endl;
using std::fstream;      using std::string;
using std::vector;       using std::stoi;
using std::swap;         using std::find;


void choosePivot(vector<int>::iterator& beg, vector<int>::iterator& end,
                                   vector<int>::iterator& pivot_position)
{
    ptrdiff_t range = end - beg;

    // randomised pivot position
    srand( time(NULL) );               // pick the seed

    int random_number = rand() % (range - 1);
    pivot_position = beg + random_number;
//    cout << "random pivot position = " << random_number << " and " << *pivot_position << endl;
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


void quickSort(vector<int>::iterator& beg, vector<int>::iterator& end)
{
    vector<int>::size_type size = end - beg;
    if (size == 1) return;

    vector<int>::iterator pivot_position;
    choosePivot(beg, end, pivot_position);

    partitionAroundPivot(beg, end, pivot_position);
//    cout << "comparisons: " << count_comparisons << endl;

    vector<int>::iterator after_pivot;
    pivot_position == end - 1 ? after_pivot = pivot_position : after_pivot = pivot_position + 1;
//    if (size > 1) {
//        for (vector<int>::iterator jter = beg; jter != after_pivot; ++jter)
//            cout << "first half: " << *jter << endl;
//        for (vector<int>::iterator jter = after_pivot; jter != end; ++jter)
//            cout << "second half: " << *jter << endl;
//    }

    quickSort(beg, after_pivot);
    quickSort(after_pivot, end);
}


//int rSelect(vector<int>::iterator& beg, vector<int>::iterator& end, const int target_position)
//{
//    // base case
//    if (end - beg <= 1) return *beg;
//
//    // choose pivot randomly
//    vector<int>::iterator pivot_position;
//    choosePivot(beg, end, pivot_position);  // returns the pivot_position at random
//
//    vector<int>::iterator iterator_at_target_pos = beg + target_position;
//
//    // partition data array around pivot
//    partitionAroundPivot(beg, end, pivot_position);
//
//    int target_minus_pivot = 0;
//    for (vector<int>::iterator iter = beg; iter != pivot_position; iter++)
//        --target_minus_pivot;
//    if (-target_minus_pivot < target_position)  // this is: if (pivot - beg < target_position) ..
//        target_minus_pivot += target_position - 1;
//    else
//        target_minus_pivot = 0;
////    cout << "target_minus_pivot = " << target_minus_pivot << endl;
////
////    for (vector<int>::iterator jter = beg; jter != after_pivot; ++jter)
////        cout << "first half: " << *jter << endl;
////    for (vector<int>::iterator jter = after_pivot; jter != end; ++jter)
////        cout << "second half: " << *jter << endl;
//
//    vector<int>::iterator after_pivot = pivot_position + 1;
//
//    if (*pivot_position == *iterator_at_target_pos) return *pivot_position;
//    else if (pivot_position > iterator_at_target_pos) return rSelect(beg, after_pivot, target_position);
//    else return rSelect(after_pivot, end, target_minus_pivot);
//
//    //return 0;           // it never gets here
//}


int dSelect(vector<int>::iterator& beg, vector<int>::iterator& end, const int target_position)
{
    ptrdiff_t length = end - beg;
    // base case
    if (length == 1) return *beg;

    // break array in subarrays of 5 elements each
    int subarray_length = length / 5;
    vector<int> medians;
    int counter = 1;
    for (vector<int>::iterator iter = beg; iter < beg + 5 * subarray_length; iter += subarray_length) {
        vector<int>::iterator second_iter = beg + counter * subarray_length;
        ++counter;
        quickSort(iter, second_iter);
        if (subarray_length % 2 == 0)     // even array size
            medians.push_back(*(iter + subarray_length / 2 - 1));
        else
            medians.push_back(*(iter + subarray_length / 2));
    }
    if (end > beg + 5 * subarray_length) {
        vector<int>::iterator iter = beg + 5 * subarray_length;
        quickSort(iter, end);
        if ((end - iter) % 2 == 0)
            medians.push_back(*(iter + (end - iter) / 2 - 1));
        else
            medians.push_back(*(iter + (end - iter) / 2));
    }

//    cout << "medians: " << endl;
//    for (size_t i = 0; i != medians.size(); ++i) {
//        cout << medians[i] << " ";
//    }
//    cout << endl;

//    cout << "input data: " << endl;
//    for (vector<int>::iterator iter = beg; iter != end; ++iter) {
//        cout << *iter << " ";
//    }
//    cout << endl;

    int median_pivot_position;
    if (medians.size() % 2 == 0)
        median_pivot_position = medians.size() / 2 - 1;
    else
        median_pivot_position = medians.size() / 2;
    // returns the pivot_position as the 'median of medians'
    vector<int>::iterator medians_beg = medians.begin();
    vector<int>::iterator medians_end = medians.end();
    quickSort(medians_beg, medians_end);
    static int median_of_medians_counter;
    int median_of_medians;
//    cout << "counter: " << median_of_medians_counter << endl;
    if (median_of_medians_counter != 0) {
        --median_of_medians_counter;// = 0;
        return *(medians_beg + median_pivot_position);
    }
    else {
        ++median_of_medians_counter;
        median_of_medians = dSelect(medians_beg, medians_end, median_pivot_position);
    }

//    cout << "medians: " << endl;
//    for (size_t i = 0; i != medians.size(); ++i) {
//        cout << medians[i] << " ";
//    }
//    cout << " pivot= " << *(medians.begin() + median_pivot_position) <<
//            " pivot position= " << median_pivot_position << endl;
//    cout << "median of medians: " << median_of_medians << endl;

    vector<int>::iterator iterator_at_median_pivot_pos = medians.begin() + median_pivot_position;
    vector<int>::iterator pivot_position = find(beg, end, *iterator_at_median_pivot_pos);
    // partition data array around pivot
//    cout << "iterator at pivot in medians: " << *iterator_at_median_pivot_pos
//         << " in input array: " << *pivot_position << endl;

    partitionAroundPivot(beg, end, pivot_position);
//    cout << "input after partition around pivot: " << endl;
//    for (vector<int>::iterator iter = beg; iter != end; ++iter) {
//        cout << *iter << " ";
//    } cout << endl;

    int target_minus_pivot = 0;
    for (vector<int>::iterator iter = beg; *iter != *pivot_position; iter++)
        --target_minus_pivot;
    if (-target_minus_pivot < target_position)  // this is: if (pivot - beg < target_position) ..
        target_minus_pivot += target_position - 1;
    else
        target_minus_pivot = 0;
//////    cout << "target_minus_pivot = " << target_minus_pivot << endl;
//////
//////    for (vector<int>::iterator jter = beg; jter != after_pivot; ++jter)
//////        cout << "first half: " << *jter << endl;
//////    for (vector<int>::iterator jter = after_pivot; jter != end; ++jter)
//////        cout << "second half: " << *jter << endl;

    vector<int>::iterator after_pivot = pivot_position + 1;
    vector<int>::iterator iterator_at_target_pos = beg + target_position;
    if (*pivot_position == *iterator_at_target_pos) return *pivot_position;
    else if (pivot_position > iterator_at_target_pos) return dSelect(beg, after_pivot, target_position);
    else return dSelect(after_pivot, end, target_minus_pivot);
}


int main(int argc, char** argv)
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
//            cout << element << endl;
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

    int median = dSelect(beg, end, median_pos);

//    for(vector<int>::const_iterator iter = data_array.begin(); iter != data_array.end(); ++iter) {
//        cout << *iter << " ";
//    }
//    cout << endl;

    //input.open(filename, fstream::out | fstream::trunc);
    cout << "Median of given array of integers is: " << median << " at position " << median_pos << endl;
    //input.close();

    return 0;
}
