// sorts sequence of unsorted integers from input file
// counts the inversions while sorting, e.g:
// 3 2 1 4 --> 1 2 3 4, with 1 inversion
#include <iostream>
#include <fstream>
#include <cstdint>  // allows the uintmax_t larger int type
#include <limits>   // std::numeric_limits

using namespace std;

uintmax_t imin = numeric_limits<uintmax_t>::min(); // minimum value
uintmax_t imax = numeric_limits<uintmax_t>::max();

// mergeSort recursive function that also counts inversions while sorting
uintmax_t sortCount(int* input, int input_size)
{
    // split input array in two halves, smaller arrays 'a' and 'b'
    // not made into a function because would have to pass back pointers on return
    int* a;
    int* b;
    int size_a = input_size / 2;
    int size_b;
    if (input_size % 2 == 0) {
        size_b = size_a;
    } else {                    // in case input_size is odd the extra element will go in 'b'
        size_b = size_a + 1;
    }
    a = new int[size_a];        // need to use pointers because of sizes_a_b determined at run time
    b = new int[size_b];
    for (int i = 0; i != size_a; ++i)   // loop that assigns values
    {
        a[i] = input[i];
        b[i] = input[size_a + i];
    }
    if (input_size % 2 != 0) {              // in case of odd input_size assign the loose element out to 'b'
        b[size_b - 1] = input[input_size - 1];
    }

    uintmax_t inversions_a = 0, inversions_b = 0;
    // sort recursively split arrays 'a' and 'b'
    if (size_a > 1) {inversions_a = sortCount(a, size_a);}
    if (size_b > 1) {inversions_b = sortCount(b, size_b);}

    // main sort loop: sorted 'a' and 'b' are merged, yielding the sorted 'input' array
    uintmax_t inversions = 0;
    int i = 0, j = 0;
    for (int k = 0; k != input_size; ++k)
    {
        if ( (i < size_a) && ((j >= size_b) || (a[i] <= b[j])) ) {
            input[k] = a[i];
            i++;
        } else if (j < size_b) {
            input[k] = b[j];
            j++;
            if (i < size_a) {
                inversions += size_a - i;   // -1 accounts for 'size_a' being = last element in (a + 1)
            }
        }
    }

    inversions += inversions_a + inversions_b;

    delete[] a;
    delete[] b;

    return inversions;
}


int main()
{
    cout << "Input array of integers: " << endl;

    ifstream input_file("countInversions_input.txt");
    const int SIZE = 100000;
    int input[SIZE];
    char input_char[8];
    string input_str = "";
    
    // uncomment if you are not inclined to input from command prompt
    //int input[] = {6, 11, 7, 4, 3, 1, 9, 0, -1, 5, 8, 10, 12, 2, 13, 98, -2};
    //int input_size = sizeof(input)/sizeof(input[0]);
    //for (int i = 0; i != input_size; ++i)
    
    for (int i = 0; i != SIZE; ++i)
    {
        input_file.getline(input_char, 8, '\n');
        input_str = input_char;
        input[i] = stoi(input_str);
    }
    input_file.close();
    int input_size = sizeof(input)/sizeof(input[0]);
    cout << " input_size: " << input_size << endl;

    uintmax_t count_inversions = 0;
    count_inversions = sortCount(input, input_size);
    cout << "Sorted array: ";
    for (int i = 0; i != input_size; ++i)
    {
        cout << input[i] << " ";
    }
    cout << endl;
    cout << "Number of inversions: " << count_inversions << endl;
    // maximum available on implementation, UINTMAX_MAX = 2^63 - 1
    cout << "imax = " << imax << " UINTMAX_MAX = " << UINTMAX_MAX << endl;

    return 0;
}
