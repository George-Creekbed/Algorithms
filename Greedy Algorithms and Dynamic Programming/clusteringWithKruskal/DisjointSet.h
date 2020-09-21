#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED

#include "Graph.h"

class DisjointSet
{
public:
    DisjointSet(const size_t);
    ~DisjointSet();
    DisjointSet& operator= (const DisjointSet&);

    int find(const Node&);
    void unionNodes(const Node&, const Node&);

    int get(int index) {return *leaders[index];}

private:
    size_t size;        // graph size needed for allocation of pointer data members below
    int* base;          // array of int each Node of the graph has its leader
    int** leaders;      // array of pointers to int, allows to reassign leaders to Nodes after unions

    int find_int(int);  // auxiliary to 'find' above

    DisjointSet(const DisjointSet&);    // copy constructor forbidden
};

#endif // DISJOINTSET_H_INCLUDED
