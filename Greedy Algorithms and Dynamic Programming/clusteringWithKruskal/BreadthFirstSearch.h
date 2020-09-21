#ifndef BREADTHFIRSTSEARCH_H_INCLUDED
#define BREADTHFIRSTSEARCH_H_INCLUDED
#include <limits>
#include "Graph.h"

int const infinity = std::numeric_limits<int>::infinity();

bool breadthFirstSearch(const Graph&, const int, const int);

#endif // BREADTHFIRSTSEARCH_H_INCLUDED
