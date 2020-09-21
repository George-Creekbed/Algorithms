// creates and manages a graph data structure
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <array>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>

class Edge
{
public:
    // constructors
    Edge();
    Edge(int, int, int);

    std::array<int, 2> getNodes() const;
    void setNodes(const int, const int);
    int getCost() const;
    void setCost(const int);
    void swapNodes();
    // a get() that allows writing:
    int operator[](const int);

//    Edge& operator=(const Edge);

    bool operator==(const Edge&) const;
    bool operator!=(const Edge&) const;

private:
    int node1, node2;       // nodes are just indices of the nodes in the graph
    int cost;
};


class Node
{
    friend class Graph;
public:
    // constructors
    Node();
    Node(const Edge&);

    inline int getLabel() const {return label;}
    Edge getEdge(const int) const;
    inline void setLabel(const int in) {label = in;}
    inline void addEdge(const Edge in) {edges.push_back(in);}
    // void addManyEdges(const std::vector<Edge>);
    inline int getScore() const {return score;}
    inline void setScore(const int in) {score = in;}

    inline std::list<Edge>::size_type size() const {return edges.size();}  // size of list 'edges'

    // iterators
    typedef std::list<Edge>::iterator iterator;
    typedef std::list<Edge>::const_iterator const_iterator;
    inline std::list<Edge>::iterator begin() {return edges.begin();}
    inline std::list<Edge>::iterator end() {return edges.end();}
    inline std::list<Edge>::const_iterator cbegin() const {return edges.begin();}
    inline std::list<Edge>::const_iterator begin() const {return edges.begin();}
    inline std::list<Edge>::const_iterator cend() const {return edges.end();}
    inline std::list<Edge>::const_iterator end() const {return edges.end();}

    // inserts group of edges to the end of a edges vector
    inline std::list<Edge>::iterator insertEdges(const std::list<Edge>::iterator beg_in,
                                                   const std::list<Edge>::iterator end_in)
    {
        return edges.insert(end(), beg_in, end_in);
    }
    // erase node
    std::list<Edge>::iterator erase(int);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

private:
    int label;
    std::list<Edge> edges;
    int score;          // new, starts at 10000000, is equal to lowest cost Edge in 'edges'
};


class Graph
{
public:
    Graph();
    // constructor from txt file
    Graph(const std::string&);

    inline Node getNode(const int index) const {return nodes[index];}
    inline void addNode(const Node in) {nodes.push_back(in);}

    inline std::vector<Node>::size_type size() {return nodes.size();}  // size of vector 'nodes'
    inline std::vector<Node>::size_type size() const {return nodes.size();}  // size of vector 'nodes'
    void output() const;      // prints graph
    void output(const int) const;

    // iterators
    typedef std::vector<Node>::iterator iterator;
    typedef std::vector<Node>::const_iterator const_iterator;
    inline std::vector<Node>::iterator begin() {return nodes.begin();}
    inline std::vector<Node>::iterator end() {return nodes.end();}
    inline std::vector<Node>::const_iterator begin() const {return nodes.begin();}
    inline std::vector<Node>::const_iterator end() const {return nodes.end();}

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
};

bool compareCosts(const Edge&, const Edge&);
bool compareScores(const Node&, const Node&);
bool compareLabels(const Node&, const Node&);


//#include "Graph.cpp"
#endif // GRAPH_H_INCLUDED
