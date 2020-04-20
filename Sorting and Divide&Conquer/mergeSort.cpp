#include <iostream>

using namespace std;

void mergeSort(int* input, int input_size)
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

    // sort recursively split arrays 'a' and 'b'
    if (size_a > 1) {mergeSort(a, size_a);}
    if (size_b > 1) {mergeSort(b, size_b);}

//    cout << "size a: " << size_a << ", array a: ";    // debugging
//    for (int i = 0; i != size_a; ++i)
//    {
//        cout << a[i] << " ";
//    }
//    cout << endl;
//    cout << "size b: " << size_b << ", array b: ";
//    for (int i = 0; i != size_b; ++i)
//    {
//        cout << b[i] << " ";
//    }
//    cout << endl;                                     // debugging

    // main sort loop: sorted 'a' and 'b' are merged yielding the sorted 'input' array
    int i = 0, j = 0;
    for (int k = 0; k != input_size; ++k)
    {
        if ( (i < size_a) && ((j >= size_b) || (a[i] <= b[j])) ) {
            input[k] = a[i];
            i++;
        } else if (j < size_b) {
            input[k] = b[j];
            j++;
        }
    }

    delete[] a;
    delete[] b;

    return;
}


int main()
{
    cout << "Input array of integers: " << endl;
    int input[] = {5, 8, 6, 4, 3, 2, 7, 1, 0, 4, 6, 7, 8, 2, 12, 98, -2};
    int input_size = sizeof(input)/sizeof(input[0]);
    for (int i = 0; i != input_size; ++i)
    {
        cout << input[i] << " ";
    }
    cout << " input_size: " << input_size << endl;

    mergeSort(input, input_size);
    cout << "Sorted array: ";
    for (int i = 0; i != input_size; ++i)
    {
        cout << input[i] << " ";
    }
    cout << endl;

    return 0;
}
