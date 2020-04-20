#include <iostream>         // cout, endl, cin
#include <stdlib.h>         // srand, rand
#include <algorithm>        // min, max_element, swap, equal

#include "Point2D.h"
#include "mergeSort.cpp"

using std::cin;         using std::endl;
using std::cout;        using std::rand;
using std::srand;       using std::min;
using std::max_element; using std::swap;
using std::equal;

// checks whether Point2D 'input' lies at horizontal (x-axis) 'distance' from Point2D 'frontier'
bool checkXDistance(const Point2D& input, const Point2D& frontier, const double& distance)
{
    return (abs(input.getX() - frontier.getX()) <= distance);
}


// finds closest pairs that are split between upper and lower sub-arrays (Q and R) of starting array P
Point2D* closestSplitPair(Point2D* Qx, Point2D* Rx, const int Q_size, const int R_size, double& shortest_distance)
{
    Point2D* best_pair = new Point2D[2];    // declare return value 'best_pair'
    Point2D frontier_point = *max_element(Qx, Qx + Q_size, compareX);   // middle value out of range of possible split pairs

    if (Q_size < 4) {      // base cases Q_size = 2 or 3
        if (equal(Qx, Qx + Q_size, Rx)) {   // case where P_size < 4, then P = Q = R as found in closestPair function
            for (int i = 0; i != Q_size; ++i) {
                for (int j = i + 1; j != Q_size; ++j) {
                    if (distance(Qx[i], Qx[j]) == shortest_distance) {
                        best_pair[0] = Qx[i];
                        best_pair[1] = Qx[j];
                    }
                }
            }
        } else {         // case where Q and R have size 2 or 3 but P is bigger
            for (int i = 0; i != Q_size; ++i) {
                for (int j = 0; j != R_size; ++j) {
                    if ( (distance(Qx[i], Rx[j]) <= shortest_distance) &&
                        (Qx[i].getOrdinal() != Rx[j].getOrdinal()) ){
                        best_pair[0] = Qx[i];
                        best_pair[1] = Rx[j];
                        shortest_distance = distance(Qx[i], Rx[j]);
                    }
                }
            }
        }
        return best_pair;
    }                                   // end base-cases

    // identify close pairs split between Q and R
    Point2D S[Q_size + R_size];         // array of Point2Ds representing a range straddling in the middle of Q and R
    int j = 0;
    for (int i = 0; i != Q_size; ++i) {
        if (checkXDistance(Qx[i], frontier_point, shortest_distance)){
            S[j++] = Qx[i];
        }
    }
    for (int i = 0; i != R_size; ++i) {
        if (checkXDistance(Rx[i], frontier_point, shortest_distance)){
            S[j++] = Rx[i];
        }
    }
    int S_size = j;
    mergeSort(S, S_size, compareY);         // sort S by _y

    // main loop of the algorithm, inner computation decreases computational cost o(n^2) -> o(7n)
    double max_points_in_range;
    if (S_size < 8) {       // in case of small array P
        max_points_in_range = 0;
        for (int i = 0; i != S_size; ++i) {
            for (int j = i + 1; j < S_size; ++j) {
                double distance_temp = distance(S[i], S[j]);
                if (distance_temp < shortest_distance) {
                    shortest_distance = distance_temp;
                    best_pair[0] = S[i];
                    best_pair[1] = S[j];
                }
            }
        }
    } else {        // bigger array P, canonical algorithm form
        max_points_in_range = 7;
        for (int i = 0; i != S_size - max_points_in_range; ++i) {
            for (int j = 1; j < 8; ++j) {
                double distance_temp = distance(S[i], S[i + j]);
                if (distance_temp < shortest_distance) {
                    shortest_distance = distance_temp;
                    best_pair[0] = S[i];
                    best_pair[1] = S[i + j];
                }
            }
        }
    }

    return best_pair;
}


Point2D* closestPair(Point2D* P, const int P_size, double& shortest_distance)
{
    // deal with singular cases
    if (P_size == 1) {
        const char* error = "Input an array of at least 2 elements\n";
        throw error;
    }

    // STEP 0: create P_x
    Point2D* P_x = new Point2D[P_size];
    for (int i = 0; i != P_size; ++i)
    {
        P_x[i] = P[i];
    }
    mergeSort(P_x, P_size, compareX);

    // STEP 1: split P_x in Q_x and R_x
    int Q_size = P_size / 2;
    int R_size;
    if (P_size % 2 == 0) {
        R_size = Q_size;
    } else {                 // in case P_size is odd the extra element will go in 'R'
        R_size = Q_size + 1;
    }

    // singular case: forget above if P_size < 4
    if (P_size < 4) {
        Q_size = P_size;
        R_size = P_size;
    }

    Point2D* Q_x = new Point2D[Q_size];
    for (int i = 0; i != Q_size; ++i)
    {
        Q_x[i] = P_x[i];
    }

    Point2D* R_x = new Point2D[R_size];
    if (P_size > 3) {
        for (int i = 0; i != R_size; ++i)
        {
            R_x[i] = P_x[Q_size + i];
        }
    } else {
        for (int i = 0; i != R_size; ++i)
        {
            R_x[i] = P_x[i];
        }
    }

    // STEP 2 & 3: choose closest pair in Q and R
    Point2D* closest_pair_Q = new Point2D[Q_size];
    double shortest_distance_Q = distance(P[0], P[1]);  // initial value
    if (Q_size > 3) {   // recursion
        closest_pair_Q = closestPair(Q_x, Q_size, shortest_distance);
    }
    else {                             // compute shortest pair if Q_size = 2 ...
        for (int i = 0; i != Q_size; ++i) {
            closest_pair_Q[i] = Q_x[i];
        }
        shortest_distance_Q = distance(Q_x[0], Q_x[1]);
        if (Q_size == 3) {            // ...compute shortest pair if Q_size = 3
            for (int i = 0; i != 2; ++i) {
                double distance_temp = distance(Q_x[i], Q_x[2]);
                if (distance_temp < shortest_distance_Q) {
                    shortest_distance_Q = distance_temp;
                    swap(closest_pair_Q[0], closest_pair_Q[i]);
                    swap(closest_pair_Q[1], closest_pair_Q[2]);
                }
            }
        }
    }

    Point2D* closest_pair_R = new Point2D[R_size];
    double shortest_distance_R = distance(P[0], P[1]); // initial value
    if (R_size > 3) {           // recursion
        closest_pair_R = closestPair(R_x, R_size, shortest_distance);
    }
    else {
        for (int i = 0; i != R_size; ++i) {     // calculate shortest pair if R_size = 2...
            closest_pair_R[i] = R_x[i];
        }
        shortest_distance_R = distance(R_x[0], R_x[1]);
        if (R_size == 3) {                  // ...calculate shortest pair if R_size = 3
            for (int i = 0; i != 2; ++i) {
                double distance_temp = distance(R_x[i], R_x[2]);
                if (distance_temp < shortest_distance_R) {
                    shortest_distance_R = distance_temp;
                    swap(closest_pair_R[0], closest_pair_R[i]);
                    swap(closest_pair_R[1], closest_pair_R[2]);
                }
            }
        }
    }

    // STEP 4: search for closest pair that may have one element in each of Q and R
    double shortest_distance_QR = min(shortest_distance_Q, shortest_distance_R);
    Point2D* closest_pair_inbetween = new Point2D[2];
    closest_pair_inbetween = closestSplitPair(Q_x, R_x, Q_size, R_size, shortest_distance_QR);
    shortest_distance = min(shortest_distance, shortest_distance_QR);

    // avoid memory leaks
    delete[] P_x;
    delete[] Q_x;
    delete[] R_x;

    // STEP 5: output closest pair out of Q, R, or split between Q and R
    if (shortest_distance == shortest_distance_QR) {    // we are at the base recursive level, Q_size = 2 or 3
        if (shortest_distance_Q == shortest_distance_QR) {
            delete[] closest_pair_R;
            delete[] closest_pair_inbetween;
            return closest_pair_Q;
        } else if (shortest_distance_R == shortest_distance_QR) {
            delete[] closest_pair_Q;
            delete[] closest_pair_inbetween;
            return closest_pair_R;
        } else {
            delete[] closest_pair_Q;
            delete[] closest_pair_R;
            return closest_pair_inbetween;
        }
    } else {    // we are unfolding the recursion tree
        shortest_distance_Q = distance(closest_pair_Q[0], closest_pair_Q[1]);
        shortest_distance_R = distance(closest_pair_R[0], closest_pair_R[1]);
        if (shortest_distance_Q <= shortest_distance_R) {
            delete[] closest_pair_R;
            delete[] closest_pair_inbetween;
            return closest_pair_Q;
        } else {
            delete[] closest_pair_Q;
            delete[] closest_pair_inbetween;
            return closest_pair_R;
        }
    }

    return P;   // never reaches this point, just to make the compiler happy
}


int main()
{
    cout << "Please select size of array of random numbers: ";
    int SET_SIZE;
    cin >> SET_SIZE;
    cout << endl;

    Point2D points[SET_SIZE];
    // generate points randomly in the range (x,y) \in [0, SET_SIZE]
    cout << "Set of points: \n";
    for (int i = 0; i != SET_SIZE; ++i)
    {
        srand(SET_SIZE * SET_SIZE / 2 + i);
        points[i] = Point2D{(double) (rand() % SET_SIZE), (double) ((rand()+1) % SET_SIZE), i + 1};  // Point2D{x, y, ordinal}
        cout << "point " << points[i].getOrdinal() << "  x:" << points[i].getX() << " y:" << points[i].getY() << endl;
    }
    // sort arrays by x or y
//    cout << "Sort set by x: " << endl;
//    mergeSort(points, SET_SIZE, compareX);
//    for (int i = 0; i != SET_SIZE; ++i)
//    {
//        cout << "point " << points[i].getOrdinal() << "  x:" << points[i].getX() << " y:" << points[i].getY() << endl;
//    }
//    cout << "Sort set by y: " << endl;
//    mergeSort(points, SET_SIZE, compareY);
//    for (int i = 0; i != SET_SIZE; ++i)
//    {
//        cout << "point " << points[i].getOrdinal() << "  x:" << points[i].getX() << " y:" << points[i].getY() << endl;
//    }
//    cout << "Sort set by ordinal: " << endl;
//    mergeSort(points, SET_SIZE, compareOrdinal);
//    for (int i = 0; i != SET_SIZE; ++i)
//    {
//        cout << "point " << points[i].getOrdinal() << "  x:" << points[i].getX() << " y:" << points[i].getY() << endl;
//    }

    Point2D* closest_pair;  // null pointer
    double shortest_distance = distance(points[0], points[1]);  // initialiser value for shortest_distance
//    cout << "initial shortest distance " << shortest_distance << endl;
    try {closest_pair = closestPair(points, SET_SIZE, shortest_distance);}    // points to final result
    catch (const char* error) {cout << error << "\n";}

    ////////////////////
    // output result: //
    ////////////////////
    cout << endl;
    cout << "Closest pair of points are point " << closest_pair[0].getOrdinal() << " and point "
         << closest_pair[1].getOrdinal() << ",\n";
    cout << "at positions (" << closest_pair[0].getX() << "," << closest_pair[0].getY() << ") and ("
         << closest_pair[1].getX() << "," << closest_pair[1].getY() << "),\n";
    cout << "at a distance of " << distance(closest_pair[0], closest_pair[1]) << "." << endl;  // debug: " or " << shortest_distance <<

    delete[] closest_pair;  // avoid memory leak

    return 0;
}
