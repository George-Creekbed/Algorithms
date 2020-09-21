// Union-find structure (lazy unions)
#include "DisjointSet.h"

DisjointSet::DisjointSet(size_t in): size(in), base(new int[in]), leaders(new int*[in])
{
    for (size_t i = 1; i != in + 1; ++i) {
        base[i - 1] = i;
        leaders[i - 1] = &base[i - 1];
    }
}


DisjointSet::~DisjointSet()
{
    delete[] base;
    delete[] leaders;
}


DisjointSet& DisjointSet::operator= (const DisjointSet& rhs)
{
    if (this == &rhs)
        return *this;       // make sure you aren't self-assigning
    if (base != NULL) {
        delete[] leaders;     // get rid of the old data
        delete[] base;
    }

    // "copy constructor" from here
    size = rhs.size;
    base = new int[size];
    leaders = new int*[size];
    base = rhs.base;
    for (size_t i = 0; i != size; ++i)
        leaders[i] = &base[i];

    return *this;
}


// auxiliary to find: implements the recursion
int DisjointSet::find_int(int leader_pos)
{
    int parent(leader_pos);
    if (leader_pos != *leaders[leader_pos - 1])
        parent = find_int(*leaders[leader_pos - 1]);

    return parent;
}


// returns leader to input Node
int DisjointSet::find(const Node& input)
{
    int parent( input.getLabel() );
    if (input.getLabel() != *leaders[input.getLabel() - 1])
        parent = find_int(*leaders[input.getLabel() - 1]);

    return parent;
}


// merges sets by assigning same leader (the lesser of the two Nodes)
void DisjointSet::unionNodes(const Node& a, const Node& b)
{
    if (find(a) != find(b)) {
        if (find(a) < find(b))
            leaders[find(b) - 1] = &base[find(a) - 1];
        else
            leaders[find(a) - 1] = &base[find(b) - 1];
    }
}
