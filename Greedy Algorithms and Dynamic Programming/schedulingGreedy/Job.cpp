#include "Job.h"

// constructors
Job::Job(): _weight(0), _length(0) {}
Job::Job(double w, double l): _weight(w), _length(l) {}


// get functions
int Job::getWeight()
{
    return _weight;
}


int Job::getLength()
{
    return _length;
}


// score functions
int Job::scoreSubtraction()
{
    return _weight - _length;
}


double Job::scoreDivision()
{
    return _weight / _length;
}


// helps with  main program readability
int Job::completionTime()
{
    return _length;
}
