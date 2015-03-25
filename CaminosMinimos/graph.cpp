#include "graph.hpp"

DirectedEdge::DirectedEdge(int v, int w, double weight)
{
    this->v = v;
    this->w = w;
    this->weight = weight;
}

std::string DirectedEdge::toString()
{
    std::ostringstream  ss;
    ss << v;
    std::string vs = ss.str();
    std::ostringstream  ss2;
    ss2 << w;
    std::string vw = ss2.str();
    return vs + " -> " + vw + " ";
}

EdgeWeightedDigraph::EdgeWeightedDigraph(int v)
{
    this->v = v;
    adjacent = new std::list<DirectedEdge>[v];
}

void EdgeWeightedDigraph::addEdge(DirectedEdge e)
{
    int v = e.from();
    adjacent[v].push_back(e);
}

std::list<DirectedEdge> EdgeWeightedDigraph::adj(int index)
{
    return adjacent[index];
}

int EdgeWeightedDigraph::vertices()
{
    return v;
}
