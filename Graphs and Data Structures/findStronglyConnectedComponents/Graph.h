// creates and manages a graph data structure
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

class Edge
{
public:
    Edge();
    Edge(int, int);

    std::vector<int> getNodes() const;
    void setNodes(const int, const int);

    int operator[](const int);

//    Edge& operator=(const Edge);

    bool operator==(const Edge&) const;
    bool operator!=(const Edge&) const;

private:
    int node1, node2;       // nodes are just indices of the nodes in the graph
};


class Node
{
    friend class Graph;
public:
    Node();

    inline int getLabel() const {return label;}
    inline Edge getEdge(const int index) const {return edges[index];}
    inline Edge& modifEdge(const int index) {return edges[index];}
    inline void setLabel(const int in) {label = in;}
    inline void addEdge(const Edge in) {edges.push_back(in);}
    void addManyEdges(const std::vector<Edge>);
    inline void reserve(const int in) {edges.reserve(in);};

    inline std::vector<Edge>::size_type size() const {return edges.size();}  // size of vector 'edges'
    // iterators
    inline std::vector<Edge>::iterator begin() {return edges.begin();}
    inline std::vector<Edge>::iterator end() {return edges.end();}
    inline Edge& operator[] (const int index)
    {
        return edges[index];
    }
    // inserts group of edges to the end of a edges vector
    inline std::vector<Edge>::iterator insertEdges(const std::vector<Edge>::iterator beg_in,
                                                   const std::vector<Edge>::iterator end_in)
    {
        return edges.insert(end(), beg_in, end_in);
    }
    // erase node
    inline std::vector<Edge>::iterator erase(const int index)
    {
        return edges.erase(edges.begin() + index);
    }

private:
    int label;
    std::vector<Edge> edges;
};


class Graph
{
public:
    Graph();
    // constructor from txt file
    Graph(const std::string&, const std::string& = "long");

    inline void reserve(const int in) {nodes.reserve(in);};
    inline Node getNode(const int index) const {return nodes[index];}
    inline void addNode(const Node in) {nodes.push_back(in);}

    inline std::vector<Node>::size_type size() {return nodes.size();}  // size of vector 'nodes'
    inline std::vector<Node>::size_type size() const {return nodes.size();}  // size of vector 'nodes'
    void output() const;      // prints graph
    void output(const int) const;

    // iterators
    inline std::vector<Node>::iterator begin() {return nodes.begin();}
    inline std::vector<Node>::iterator end() {return nodes.end();}

    inline Node& operator[](const int index)
    {
        return nodes[index];
    }
    inline std::vector<Node>::iterator erase(const int index)
    {
        return nodes.erase(nodes.begin() + index);
    }

private:
    std::vector<Node> nodes;

    void importShortFile(std::ifstream&);
    void importLongFile(std::ifstream&);
};

bool compareEdges(const Edge&, const Edge&);
bool compareNodes(const Node&, const Node&);

//#include "Graph.cpp"
#endif // GRAPH_H_INCLUDED
