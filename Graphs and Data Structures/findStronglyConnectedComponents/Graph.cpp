#ifndef GRAPH_CPP_INCLUDED
#define GRAPH_CPP_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Graph.h"

using std::vector;      using std::ifstream;
using std::string;      using std::stoi;
using std::cout;        using std::endl;
using std::sort;

Edge::Edge(): node1(0), node2(0) {}
Edge::Edge(int node_1, int node_2)
{
    node1 = node_1;
    node2 = node_2;
}


vector<int> Edge::getNodes() const
{
    vector<int> ret;
    ret.push_back(node1);
    ret.push_back(node2);

    return ret;
}


void Edge::setNodes(const int in1, const int in2)
{
    node1 = in1;
    node2 = in2;
}


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
    if ( (node1 == rhs.getNodes()[0]) && (node2 == rhs.getNodes()[1]) ) return true;
    else return false;
}


bool Edge::operator!=(const Edge& rhs) const
{
    if ( !(*this == rhs) ) return true;
    else return false;
}


Node::Node(): label(0) {}
void Node::addManyEdges(const vector<Edge> input)
{
    for (size_t i = 0; i != input.size(); i++)
    {
        edges.push_back(input[i]);
    }
}

bool compareEdges(const Edge& a, const Edge& b)
{
    bool ret = (a.getNodes()[0] < b.getNodes()[0]);
    if ( (a.getNodes()[0] == b.getNodes()[0]) )
        ret = a.getNodes()[1] < b.getNodes()[1];

    return ret;
}

bool compareNodes(const Node& a, const Node& b)
{
    return (a.getLabel() < b.getLabel());
}

// auxiliary functions to build a Graph from external file data
// if file is short and unsorted
void Graph::importShortFile(ifstream& is)
{
    vector<Edge> unsorted_input;
    Node old_node;  // 2 aux. Nodes (old_node and current_node) needed to process file
    string tail_node_str, end_node_str;
    while (is)
    {
        is >> tail_node_str >> end_node_str;    // read edge on current line
        int tail_node = stoi(tail_node_str);    // str -> int
        int end_node = stoi(end_node_str);

        Edge current_edge;                      // store data out of current line in an Edge
        current_edge.setNodes(tail_node, end_node);

        unsorted_input.push_back(current_edge);
        if ( is.eof() ) break;
    }

    sort(unsorted_input.begin(), unsorted_input.end(), compareEdges); // necessary to find sink nodes if input unsorted

    for (size_t i = 0; i != unsorted_input.size(); ++i) {
        int tail_node = unsorted_input[i].getNodes()[0];    // str -> int
        int end_node = unsorted_input[i].getNodes()[1];

        Edge current_edge;                      // store current line data in an Edge
        current_edge.setNodes(tail_node, end_node);

        Node current_node;
        if ( tail_node != old_node.getLabel() ) {   // in case the line belongs to a new Node ...
            current_node.setLabel(tail_node);       // ... create a new Node ...
            current_node.addEdge(current_edge);     // ... and store the current Edge there
            if (old_node.getLabel() != 0)
                addNode(old_node);                  // add previous Node (not Node 0 though) to the Graph
            // code below finds and adds any possible sink Nodes between old_ and current_node
            if (tail_node != old_node.getLabel() + 1) {
                int node_difference = tail_node - old_node.getLabel();
                int counter = 1;
                while (node_difference != 1) {
                    Node sink_node;
                    sink_node.setLabel(old_node.getLabel() + counter);
                    addNode(sink_node);
                    node_difference--;
                    counter++;
                }
            }
            old_node = current_node;
        } else {                                    // in case data in the line belongs to the old_node
            old_node.addEdge(current_edge);
        }
//        cout << current_edge.getNodes()[0] << "  " << current_edge.getNodes()[1] << ";" << endl;  // debug

        if (i == unsorted_input.size() - 1)
            addNode(current_node);
    }
}

// if file is long and sorted
void Graph::importLongFile(ifstream& is)
{
    Node old_node;  // 2 aux. Nodes (old_node and current_node) needed to process file
    string tail_node_str, end_node_str;
    while (is)
    {
        is >> tail_node_str >> end_node_str;    // read edge on current line
        int tail_node = stoi(tail_node_str);    // str -> int
        int end_node = stoi(end_node_str);

        Edge current_edge;                      // store data out of current line in an Edge
        current_edge.setNodes(tail_node, end_node);

        Node current_node;
        if ( tail_node != old_node.getLabel() ) {   // in case the line belongs to a new Node ...
            current_node.setLabel(tail_node);       // ... create a new Node ...
            //getNode(i++).reserve(120); // slows the code down, total time 0.5s more
            current_node.addEdge(current_edge);     // ... and store the current Edge there
            if (old_node.getLabel() != 0)
                addNode(old_node);                  // add previous Node (not Node 0 though) to the Graph
            // code below finds and adds any possible sink Nodes between old_ and current_node
            if (tail_node != old_node.getLabel() + 1) {
                int node_difference = tail_node - old_node.getLabel();
                int counter = 1;
                while (node_difference > 1) {
                    Node sink_node;
                    sink_node.setLabel(old_node.getLabel() + counter);
                    addNode(sink_node);
                    node_difference--;
                    counter++;
                }
            }
            old_node = current_node;
        } else {                                    // in case data in the line belongs to the old_node
            old_node.addEdge(current_edge);
        }
//        if (tail_node % 10000 == 0) {             // debug
//            cout << current_edge.getNodes()[0] << "  " << current_edge.getNodes()[1] << ";" << endl;
//        }
        if ( is.eof() ) {
            addNode(old_node);
            break;
        }
    }
}


Graph::Graph() {}
// constructor from (huge) file scc_input.txt (each edge occupies a line in the .txt)
Graph::Graph(const string& file_input, const string& flag)
{
    nodes.reserve(875715);  // the Graph in scc_input.txt has 875714 nodes
    string filename(file_input + ".txt");
    ifstream is;
    is.open(filename);

    if (flag == "long")
        importLongFile(is);
    else if (flag == "short")
        importShortFile(is);
    else {
        try
            {throw 1;}
        catch (...)
            {cout << "Error: input in constructor-from-file either long or short as second parameter.\nAbort." << endl;}
    }

    is.close();
}


// prints all input nodes
void Graph::output() const
{
    for (size_t i = 0; i != nodes.size(); ++i)
    {
        cout << "Node " << nodes[i].getLabel() << ", with edges: ";
        for (size_t j = 0; j != nodes[i].edges.size(); ++j)
        {
            int node_left = nodes[i].getEdge(j).getNodes()[0];
            int node_right = nodes[i].getEdge(j).getNodes()[1];
            cout << node_left << "-" << node_right  << " ";
        }
        cout << endl;
    }
    cout << endl;
}


// prints 10 neighbours around picked node
void Graph::output(const int picked_node) const
{
    for (int i = picked_node - 2; i != picked_node + 3; ++i)
    {
        cout << "Node " << nodes[i].getLabel() << ", with edges: ";
        for (size_t j = 0; j != nodes[i].edges.size(); ++j)
        {
            int node_left = nodes[i].getEdge(j).getNodes()[0];
            int node_right = nodes[i].getEdge(j).getNodes()[1];
            cout << node_left << "-" << node_right  << " ";
        }
        cout << endl;
    }
    cout << endl;
}

#endif // GRAPH_CPP_INCLUDED
