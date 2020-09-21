#ifndef JOB_H_INCLUDED
#define JOB_H_INCLUDED

class Job
{
public:
    Job();
    Job(double, double);

    int getWeight();
    int getLength();

    int scoreSubtraction();
    double scoreDivision();
    int completionTime();   // not complete, weight*length of current member only, lacks previous terms

private:
    double _weight;
    double _length;
};
#include "Job.cpp"

#endif // JOB_H_INCLUDED
