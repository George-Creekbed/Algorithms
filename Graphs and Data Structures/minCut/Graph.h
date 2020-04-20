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
    Edge() {}
    Edge(int node_1, int node_2) {
        node1 = node_1; 
        node2 = node_2;
    }

    std::vector<int> getNodes() const;
    void setNodes(const int, const int);

    int& operator[](const int index)
    {
        if (index == 0) return node1;
        else if (index == 1) return node2;
        else std::cout << "edge index must be either 0 or 1" << std::endl;
    }

//    Edge& operator=(const Edge rhs) {  // assignment operator
//    if (&rhs != this) {
//        int a = rhs.getNodes()[0];
//        int b = rhs.getNodes()[1];
//        setNodes(a, b);
//    }
//
//    return *this;
//    }

    bool operator==(const Edge& rhs) const
    {
        if ( (node1 == rhs.getNodes()[0]) && (node2 == rhs.getNodes()[1]) ) return true;
        else return false;
    }

    bool operator!=(const Edge& rhs) const
    {
        if ( !(*this == rhs) ) return true;
        else return false;
    }

private:
    int node1, node2;       // nodes are just indices of the nodes in the graph
};


class Node
{
    friend class Graph;
public:
    Node(): label(0) {}

    int getLabel() const {return label;}
    Edge getEdge(const int index) const {return edges[index];}
    void setLabel(const int in) {label = in;}
    void addEdge(const Edge in) {edges.push_back(in);}
    void addManyEdges(const std::vector<Edge>);

    std::vector<Edge>::size_type size() const {return edges.size();}  // size of vector 'edges'
    // iterators
    std::vector<Edge>::iterator begin() {return edges.begin();}
    std::vector<Edge>::iterator end() {return edges.end();}
    Edge& operator[] (const int index)
    {
        return edges[index];
    }
    // inserts group of edges to the end of a edges vector
    std::vector<Edge>::iterator insertEdges(const std::vector<Edge>::iterator beg_in,
                                            const std::vector<Edge>::iterator end_in)
    {
        return edges.insert(end(), beg_in, end_in);
    }
    // erase node
    std::vector<Edge>::iterator erase(const int index)
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
    Graph() {}
    // constructor from txt file
    Graph(const std::string&);

    Node getNode(const int index) const {return nodes[index];}
    void addNode(const Node in) {nodes.push_back(in);}

    std::vector<Node>::size_type size() {return nodes.size();}  // size of vector 'nodes'
    void output() const;      // prints graph
    void output(const int) const;

    // iterators
    std::vector<Node>::iterator begin() {return nodes.begin();}
    std::vector<Node>::iterator end() {return nodes.end();}

    Node& operator[](const int index)
    {
        return nodes[index];
    }
    std::vector<Node>::iterator erase(const int index)
    {
        return nodes.erase(nodes.begin() + index);
    }

private:
    std::vector<Node> nodes;
};

#include "Graph.cpp"
#endif // GRAPH_H_INCLUDED
