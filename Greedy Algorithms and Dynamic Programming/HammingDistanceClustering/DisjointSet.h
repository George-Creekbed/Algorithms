#ifndef DISJOINTSET_H_INCLUDED
#define DISJOINTSET_H_INCLUDED

#include <cstddef>      // std::size_t

class DisjointSet
{
public:
    DisjointSet(const size_t);
    ~DisjointSet();
    DisjointSet& operator= (const DisjointSet&);

    int find(const int);
    void unionNodes(const int, const int);

    int get(int index) {return *leaders[index];}
    size_t getSize() {return size;}

private:
    size_t size;        // graph size needed for allocation of pointer data members below
    int* base;          // array of int each Node of the graph has its leader
    int** leaders;      // array of pointers to int, allows to reassign leaders to Nodes after unions

    int find_int(int);  // auxiliary to 'find' above

    DisjointSet(const DisjointSet&);    // copy constructor forbidden
};

#endif // DISJOINTSET_H_INCLUDED
