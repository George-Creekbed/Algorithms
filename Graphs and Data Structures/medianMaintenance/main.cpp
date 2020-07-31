// compute median maintenance of a series of numbers
// organising data either:
// 1) in two heaps (running time: O[log(n)])
// 2) in a balanced binary tree (r.t: O[n])
#include <iostream>
#include <string>
#include <fstream>
#include <queue>      // priority_queue
#include <set>        // set
#include <functional> // greater
#include <iterator>   // advance

using std::ifstream;            using std::vector;
using std::priority_queue;      using std::set;
using std::cout;                using std::endl;
using std::greater;             using std::string;

// compute median maintenance using two heaps: the median is the highest value of heap_low
int medianMaintenanceHeaps(ifstream& is)
{
    priority_queue<int> heap_low;                                   // supports extractMax
    priority_queue< int, vector<int>, greater<int> > heap_high;     // supports extractMin

    int counter(1), median(0), median_sum(0);
    cout << "Read input, compute medians and their sum ..." << endl;
    while( !is.eof() ) {
        int current;
        is >> current;

        if ( heap_low.empty() ||
             ((!heap_high.empty() && current < heap_high.top()) || current < heap_low.top()) )
            heap_low.push(current);
        else
            heap_high.push(current);

        if ( heap_low.size() < heap_high.size() ) {
            if (counter % 2 != 0 || ( heap_low.size() + 1 < heap_high.size() ) )
                heap_low.push( heap_high.top() );
                heap_high.pop();
        } else if (heap_low.size() > heap_high.size() + 1) {
            heap_high.push( heap_low.top() );
            heap_low.pop();
        }

        median = heap_low.top();
        median_sum += median;
//        cout << "median of first " << counter << " elements is: " << median
//             << ", for a (partial total)/10000 of: " << median_sum << endl;
        counter++;
    }

    return median_sum;
}


// compute median maintenance using a binary tree structure
int medianMaintenanceBinaryTree(ifstream& is)
{
    set<int> binary_tree;

    int counter(1), median(0), median_sum(0);
    cout << "Read input, compute medians and their sum ..." << endl;
    while( !is.eof() ) {
        int current;
        is >> current;

        binary_tree.insert(current);

        set<int>::iterator iter = binary_tree.begin();

        if (counter != 1) {
            if (counter % 2 == 0)
                advance(iter, (counter / 2) - 1);
            else
                advance(iter, counter / 2);
        }

//        cout << "contents of binary tree: ";
//        for (auto it = binary_tree.begin(); it != binary_tree.end(); ++it)
//            cout << *it << " ";

        median = *iter;
        median_sum += median;
//        cout << "median of first " << counter << " elements is: " << median
//             << ", for a (partial total)/10000 of: " << median_sum << endl;
        counter++;
    }

    return median_sum;
}


int main(int argc, char** argv)      // input filename: 'homework_input'
{
    string filename = argv[1];
    filename += ".txt";
    ifstream is;
    is.open(filename);

    // pick data structure: max-min heaps (priority_queue) or balanced binary tree (set)
    int result = medianMaintenanceHeaps(is);
//    int result = medianMaintenanceBinaryTree(is);

    is.close();
    cout << "median % 10000 is " << result % 10000 << endl;

    return 0;
}
