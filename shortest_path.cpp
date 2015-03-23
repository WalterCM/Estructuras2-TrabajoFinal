#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>
#include "graph.hpp"
#include "utils.hpp"

const double INFINITY = std::numeric_limits<int>::max();

class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph G, int s) : pq(G.vertex())
    {
        this->s = s;


        for (int v = 0; v < G.vertex(); v++) {
            DirectedEdge phEdge(s, v, INFINITY);
            edge.push_back(phEdge);
        }

        dist = new double[G.vertex()];

        for (int v = 0; v < G.vertex(); v++) {
            dist[v] = INFINITY;
        }
        dist[s] = 0.0;

        pq.insert(s, 0.0);
        while (!pq.isEmpty()) {
            int v = pq.deleteMin();
            for (DirectedEdge e : G.adj(v))
                relax(e);
        }
    }

    double distTo(int v)
    {
        return dist[v];
    }

    std::vector<DirectedEdge> pathTo(int v)
    {
        std::vector<DirectedEdge> path;
        for (DirectedEdge e = edge[v]; e.to() != s; e = edge[e.from()]) {
            path.push_back(e);
        }
        return path;
    }
private:
    void relax(DirectedEdge e)
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
    int s;
    double *dist;
    std::vector<DirectedEdge> edge;
    MinIndexedPQ pq;
};

int main()
{
    Graph G(5);
    G.addEdge(DirectedEdge(0, 1, 1.3));
    G.addEdge(DirectedEdge(1, 2, 2));
    G.addEdge(DirectedEdge(2, 3, 4));
    G.addEdge(DirectedEdge(0, 4, 3.1));

    DijkstraSP sp(G, 0);
    for (int v = 0; v < G.vertex(); v++) {
        std::cout << "0" << " -> " << v << " " << sp.distTo(v) << std::endl;
        for (DirectedEdge e : sp.pathTo(v)) {
            std::cout << e.toString();
            std::cout << "distancia: " << e.getWeight() << std::endl;
        }
        std::cout << std::endl;
    }
    std::exit(1);
}

