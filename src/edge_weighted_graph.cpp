
#include "edge_weighted_graph.hpp"


EdgeWeightedDigraph::EdgeWeightedDigraph(int v)
{
    createGraph(v);
}

void EdgeWeightedDigraph::createGraph(int v)
{
    this->v = v;
    adjacent = new std::list<DirectedEdge>[v];

    for (Vertex i : vertexShape) {
        vertexShape.pop_back();
    }

    for (int i = 0; i < v; i++) {
        vertexShape.push_back(Vertex(i, v));
    }
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

void EdgeWeightedDigraph::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < v; i++)
        for (DirectedEdge e : adjacent[i])
            e.draw(window);

    for (int i = 0; i < v; i++)
        vertexShape[i].draw(window);
}
