#ifndef COMPUTEHAMMINGDIST_H_INCLUDED
#define COMPUTEHAMMINGDIST_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include "DisjointSet.h"

std::tuple<std::unordered_multimap<std::string, int>, std::unordered_multimap< int, std::vector<int> > >
    inputInHashTable(std::istream&);

std::vector<int> permute1Bit(const std::vector<int>&, const int);

std::string vectorToString(const std::vector<int>&);

std::vector<std::string> createPermutations0(const std::unordered_multimap<int, std::vector<int> >&,
                                            std::unordered_multimap<std::string, int>&);

std::vector<std::string> createPermutations1(const std::unordered_multimap<int, std::vector<int> >&,
                                            std::unordered_multimap<std::string, int>&, const int);

std::vector<std::string> createPermutations2(const std::unordered_multimap<int, std::vector<int> >&,
                                            std::unordered_multimap<std::string, int>&, const int);

int mergeRepeatedNodes(const int, const std::unordered_multimap<std::string, int>&, DisjointSet&);

int computeHammingDist(const std::vector<std::string>&, const std::unordered_multimap<std::string, int>&,
                       const std::unordered_multimap<std::string, int>&, DisjointSet&, const int);

void outputHashTables(const std::unordered_multimap<std::string, int>&,
                      const std::unordered_multimap<int, std::vector<int> >&);

#endif // COMPUTEHAMMINGDIST_H_INCLUDED
