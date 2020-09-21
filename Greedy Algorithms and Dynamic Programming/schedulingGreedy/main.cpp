/* Implementation of a greedy algorithm
   to minimise weighted completion times
   of a sequence of scheduled jobs    */
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <numeric>
#include <cmath>    // abs()
#include "Job.h"

using std::cout;            using std::endl;
using std::string;          using std::ifstream;
using std::list;            using std::accumulate;
using std::abs;

// how the score is assigned to each Job determines
// its precedence in the schedule
double score(const string in, Job& job)
{
    if (in == "subtraction")
        return job.scoreSubtraction();
    else if (in == "division")
        return job.scoreDivision();
    else {
        try {throw;}
        catch(...) {cout << "enter either 'subtraction' or 'division'" << endl;}
        return -1;
    }
}


// used as 'compare' function for sorting list of Jobs
bool tieBreaker(Job& a, Job& b)
{
//    string heuristic = "subtraction";
    string heuristic = "division";

    double score_a = score(heuristic, a);
    double score_b = score(heuristic, b);

    bool ret;
    double tol = 10e-7;
    if (abs(score_a - score_b) > tol)
        ret = (score_a > score_b);
    else
        ret = a.getWeight() > b.getWeight();

    return ret;
}


int main(int argc, char** argv)     // input file is "jobs"
{
    // open input file, import data in ist of Jobs
    string filename(argv[1]);
    filename += ".txt";
    ifstream is;
    is.open(filename);

    cout << "Importing scheduling sequence from file ..." << endl;
    int total_jobs;
    is >> total_jobs;
    int first, second;
    list<Job> jobs;
    while ( !is.eof() ) {
        is >> first >> second;
        jobs.push_back( Job(first, second) );
    }
    is.close();

    // sort Jobs precedences following either 'subtraction' or 'division' score approach
    jobs.sort(tieBreaker);
//    for (auto iter = jobs.begin(); iter != jobs.end(); ++iter) {      // debug
//        cout << "sorted jobs: " << (*iter).getWeight() << " score division: ";
//        cout.precision(5);
//        cout << (*iter).scoreDivision() << " score subtraction: ";
//        cout << (*iter).scoreSubtraction() << endl;
//    }

    // compute completion times for each Job
    list<long long> completion_times;
    long long partial_cumulated(0);
    for (auto iter = jobs.begin(); iter != jobs.end(); ++iter) {
        completion_times.push_back( partial_cumulated + (*iter).completionTime() );
        partial_cumulated = completion_times.back();
//        cout << "ct: " << completion_times.back() << endl;        // debug
    }

    // assign weights to completion times one by one
    list<long long> weighted_completion_times;
    auto iter = completion_times.begin();
    auto jter = jobs.begin();
    for (; iter != completion_times.end() && jter != jobs.end(); ++iter, ++jter) {
        weighted_completion_times.push_back( *iter * (*jter).getWeight() );
//        cout << "wct: " << weighted_completion_times.back() << endl;      // debug
    }

    // sum all weighted completion times and output the result
    long long weighted_sum_completion_times(0);
    cout << "Weighted sum of cumulated completion times is: " << endl;
    cout << accumulate(weighted_completion_times.begin(), weighted_completion_times.end(), weighted_sum_completion_times)
         << endl;

    return 0;
}
