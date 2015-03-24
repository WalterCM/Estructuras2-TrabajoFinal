
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

std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
    std::vector<DirectedEdge> path;
    for (DirectedEdge e = edge[v]; e.to() != s; e = edge[e.from()]) {
        path.push_back(e);
    }
    return path;
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
