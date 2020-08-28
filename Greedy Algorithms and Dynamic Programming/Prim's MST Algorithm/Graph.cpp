#ifndef GRAPH_CPP_INCLUDED
#define GRAPH_CPP_INCLUDED

#include <array>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graph.h"

using std::array;       using std::ifstream;
using std::string;      using std::endl;
using std::cout;        using std::list;
using std::equal;

// Edge

// constructors
Edge::Edge():node1(0), node2(0), cost(0) {}
Edge::Edge(int node_1, int node_2, int len): node1(node_1), node2(node_2), cost(len) {}


array<int, 2> Edge::getNodes() const
{
    array<int, 2> ret = {node1, node2};

    return ret;
}


void Edge::setNodes(const int in1, const int in2)
{
    node1 = in1;
    node2 = in2;
}


int Edge::getCost() const
{
    return cost;
}


void Edge::setCost(const int len)
{
    cost = len;
}


void Edge::swapNodes()
{
    node1 = node1 - node2;
    node2 += node1;
    node1 = node2 - node1;
}


// same as getNodes() above
int Edge::operator[](const int index)
{
    if (index == 0) return node1;
    else if (index == 1) return node2;
    else {
        try {throw;}
        catch(...) {cout << "edge index must be either 0 or 1" << endl;}
        return 1;
    }
}


//    Edge& Edge::operator=(const Edge rhs) {  // assignment operator
//    if (&rhs != this) {
//        int a = rhs.getNodes()[0];
//        int b = rhs.getNodes()[1];
//        setNodes(a, b);
//    }
//
//    return *this;
//    }


bool Edge::operator==(const Edge& rhs) const
{
    if ( (node1 == rhs.getNodes()[0]) && (node2 == rhs.getNodes()[1]) && cost == rhs.getCost() ) return true;
    else return false;
}


bool Edge::operator!=(const Edge& rhs) const
{
    if ( !(*this == rhs) ) return true;
    else return false;
}

// Node

//constructors
Node::Node(): label(0), edges(0), score (10000000) {}
Node::Node(const Edge edg): label(edg.getNodes()[0]), edges(0), score (10000000)
{
    edges.push_back(edg);
}


Edge Node::getEdge(const int index) const
{
    Edge ret;
    list<Edge>::const_iterator iter = edges.begin();
    advance(iter, index);

    return *iter;
}


//void Node::addManyEdges(const vector<Edge> input)
//{
//    for (size_t i = 0; i != input.size(); i++)
//    {
//        edges.push_back(input[i]);
//    }
//}


list<Edge>::iterator Node::erase(int index)
{
    list<Edge>::iterator iter = edges.begin();
    advance(iter, index);

    return edges.erase(iter);
}


bool Node::operator==(const Node& rhs) const
{
    return label == rhs.getLabel() && equal( edges.begin(), edges.end(), rhs.begin() );  // no need to equate scores
}


bool Node::operator!=(const Node& rhs) const
{
    return !(*this == rhs);
}


//Graph

// constructors
Graph::Graph(): nodes(0) {}
Graph::Graph(const string& file_input): nodes(0)    // constructor from file
{
    string filename(file_input + ".txt");
    string line;
    ifstream is;
    is.open(filename);
    int number_nodes, number_edges;
    is >> number_nodes >> number_edges;
    int node1, node2, cost;
    int counter = 0;
    Edge previous_edge;
    while ( !is.eof() )
    {
        is >> node1 >> node2 >> cost;
        Edge this_edge(node1, node2, cost);
        if (counter < number_nodes) {
            Node this_node(this_edge);

            if (counter != 0) {
                previous_edge.swapNodes();
                if (counter == number_nodes - 1) {
                    this_node.erase(0);
                    this_node.setLabel( previous_edge.getNodes()[0] );
                }
                this_node.addEdge(previous_edge);
            }
            previous_edge = this_edge;

            addNode(this_node);     // add Node to Graph
        }
        if (counter >= number_nodes - 1) {
            nodes[node1 - 1].addEdge(this_edge);
            if (node1 != node2) {
                this_edge.swapNodes();
                nodes[node2 - 1].addEdge(this_edge);
            }
        }
        counter++;
    }
    is.close();
}


// prints all input nodes
void Graph::output() const
{
    for (size_t i = 0; i != nodes.size(); ++i)
    {
        cout << "Node " << nodes[i].getLabel() << ", size = " << nodes[i].edges.size() << "  with edges: ";
        for (size_t j = 0; j != nodes[i].edges.size(); ++j)
        {
            int node_left = nodes[i].getEdge(j).getNodes()[0];
            int node_right = nodes[i].getEdge(j).getNodes()[1];
            int cost = nodes[i].getEdge(j).getCost();
            int score = nodes[node_right - 1].getScore();
            cout << "[" << node_left << "-" << node_right << ", " << cost << ", " << score << "]   ";
        }
        cout << endl;
    }
}


// prints 10 neighbours around picked node
void Graph::output(const int picked_node) const
{
    for (int i = picked_node - 5; i != picked_node + 5; ++i)
    {
        cout << "Node " << nodes[i].getLabel() << ", with edges: ";
        for (size_t j = 0; j != nodes[i].edges.size(); ++j)
        {
            int node_left = nodes[i].getEdge(j).getNodes()[0];
            int node_right = nodes[i].getEdge(j).getNodes()[1];
            int cost = nodes[i].getEdge(j).getCost();
            int score = nodes[node_right - 1].getScore();
            cout << "[" << node_left << "-" << node_right << ", " << cost << ", " << score << "]   ";
        }
        cout << endl;
    }
}


bool compareCosts(const Edge& a, const Edge& b)
{
    return a.getCost() < b.getCost();
}


bool compareScores(const Node& a, const Node& b)
{
    return a.getScore() > b.getScore();
}


bool compareLabels(const Node& a, const Node& b)
{
    return a.getLabel() > b.getLabel();
}

#endif // GRAPH_CPP_INCLUDED
