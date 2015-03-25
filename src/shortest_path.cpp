#include <sstream>

#include "shortest_path.hpp"
using namespace std;


DijkstraSP::DijkstraSP(EdgeWeightedDigraph *G, int s) : pq(G->vertex())
{
    this->s = s;

    for (int v = 0; v < G->vertex(); v++) {
        DirectedEdge phEdge(s, v, INFINITY, G->vertex());
        edge.push_back(phEdge);
    }

    dist = new double[G->vertex()];

    for (int v = 0; v < G->vertex(); v++) {
        dist[v] = INFINITY;
    }
    dist[s] = 0.0;

    pq.insert(s, 0.0);
    while (!pq.isEmpty()) {
        int v = pq.deleteMin();
        for (DirectedEdge e : G->adj(v))
            relax(e);
    }
}

std::string DijkstraSP::distToString(int v)
{
    if (dist[v] == INFINITY)    return "INFINITO";
    std::ostringstream  ss;
    ss << dist[v];
    return ss.str();
}

std::list<DirectedEdge> DijkstraSP::pathTo(int v)
{
    std::vector<DirectedEdge> temp;

    for (DirectedEdge e = edge[v]; e.to() != s; e = edge[e.from()]) {
        if (e.getWeight() != INFINITY)
            temp.push_back(e);
    }

    std::list <DirectedEdge> path;
    for (DirectedEdge e : temp)
        path.push_front(e);

    return path;
}

std::string DijkstraSP::getSourceString()
{
    std::ostringstream  ss;
    ss << s;
    return ss.str();
}

void DijkstraSP::relax(DirectedEdge e)
{
    int v = e.from();
    int w = e.to();
    if (dist[w] > dist[v] + e.getWeight()) {
        dist[w] = dist[v] + e.getWeight();
        edge[w] = e;

        if (pq.contains(w)) pq.decreaseKey(w, dist[w]);
        else                pq.insert(w, dist[w]);
    }
}
