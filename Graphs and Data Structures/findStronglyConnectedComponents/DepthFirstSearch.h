#ifndef DEPTHFIRSTSEARCH_H_INCLUDED
#define DEPTHFIRSTSEARCH_H_INCLUDED

#include <vector>
#include <stack>
#include "Graph.h"

enum is_visited {not_visited, visited};  // define this here, or else the declarations below will not see it
void recursivePartDFS(const Graph&, const int, std::vector<is_visited>&, int&, std::vector<int>&, std::stack<Node>&);
void depthFirstSearch(const Graph&, const int, std::vector<is_visited>&, int&, std::vector<int>&);
Graph topologicalSort(const Graph&);

#endif // DEPTHFIRSTSEARCH_H_INCLUDED
