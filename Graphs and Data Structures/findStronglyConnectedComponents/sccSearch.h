#ifndef SCCSEARCH_H_INCLUDED
#define SCCSEARCH_H_INCLUDED

#include <vector>
#include <stack>
#include "Graph.h"

enum is_visited {not_visited, visited};  // define this here, or else the declarations below will not see it

bool compare(const int, const int);
void recursivePartDFS(const Graph&, const int, std::vector<is_visited>&, std::vector<int>&, std::stack<Node>&);
void depthFirstSearch(const Graph&, const int, std::vector<is_visited>&, std::vector<int>&, std::vector<int>&);
std::vector<int> sccSearch (const Graph&, const int);
Graph reverseGraph(const Graph&);
void driverProgram(const Graph&, std::vector<int>&, std::vector<int>&);

#endif // SCCSEARCH_H_INCLUDED
