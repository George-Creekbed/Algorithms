#ifndef KRUSKALCLUSTERING_H_INCLUDED
#define KRUSKALCLUSTERING_H_INCLUDED

#include <vector>
#include "Graph.h"
#include "DisjointSet.h"

int clusteringKruskalNaive(const Graph&, const std::vector<Edge>&, int);
int clusteringKruskalDisjointSet(const Graph& graph0, const std::vector<Edge>& edges, int);

#endif // KRUSKALCLUSTERING_H_INCLUDED
