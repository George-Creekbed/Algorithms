#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Graph.h"
#include "split.h"

using std::vector;      using std::ifstream;
using std::string;      using std::stoi;
using std::cout;        using std::endl;

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


void Node::addManyEdges(const vector<Edge> input)
{
    for (size_t i = 0; i != input.size(); i++)
    {
        edges.push_back(input[i]);
    }
}


// constructor from file
Graph::Graph(const string& file_input)
{
    string filename(file_input + ".txt");
    string line;
    ifstream is;
    is.open(filename);
    while (is)
    {
        getline(is, line);
        // split line of input
        vector<string> splitted_line_str = split(line);
        vector<int> splitted_line;
        // transform string input vector into a vector of integers
        for (size_t i = 0; i != splitted_line_str.size(); ++i)
        {
            splitted_line.push_back(stoi(splitted_line_str[i]));
        }
        // add current line data as a node in the graph
        Node current_node;
        current_node.setLabel(splitted_line[0]);
        for (size_t i = 1; i != splitted_line.size(); i++)
        {
            Edge current_edge;
            // check to see if edge is already there
            //find etc etc
            current_edge.setNodes(splitted_line[0], splitted_line[i]);
            current_node.addEdge(current_edge);
        }
        addNode(current_node);
        if (is.eof()) break;
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
            cout << node_left << "-" << node_right  << " ";
        }
        cout << endl;
    }
}
