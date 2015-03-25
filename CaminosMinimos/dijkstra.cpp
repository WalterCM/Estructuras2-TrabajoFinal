#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>
#include "graph.hpp"
#include "utils.hpp"

using namespace std;

const double INFINITY = numeric_limits<int>::max();

class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph *G, int s) : pq(G->vertices())
    {
        this->s = s;

        for (int v = 0; v < G->vertices(); v++) {
            DirectedEdge phEdge(s, v, INFINITY);
            edge.push_back(phEdge);
        }

        dist = new double[G->vertices()];

        for (int v = 0; v < G->vertices(); v++) {
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

    double distTo(int v)
    {
        return dist[v];
    }

    list<DirectedEdge> pathTo(int v)
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
    vector<DirectedEdge> edge;
    MinIndexedPQ pq;
};

int main()
{
    Graph G(8);
    G.addEdge(DirectedEdge(4, 5, 0.35));
    G.addEdge(DirectedEdge(5, 4, 0.35));
    G.addEdge(DirectedEdge(4, 7, 0.37));
    G.addEdge(DirectedEdge(5, 7, 0.28));
    G.addEdge(DirectedEdge(7, 5, 0.28));
    G.addEdge(DirectedEdge(5, 1, 0.32));
    G.addEdge(DirectedEdge(0, 4, 0.38));
    G.addEdge(DirectedEdge(0, 2, 0.26));
    G.addEdge(DirectedEdge(7, 3, 0.39));
    G.addEdge(DirectedEdge(1, 3, 0.29));
    G.addEdge(DirectedEdge(2, 7, 0.34));
    G.addEdge(DirectedEdge(6, 2, 0.4));
    G.addEdge(DirectedEdge(3, 6, 0.52));
    G.addEdge(DirectedEdge(6, 0, 0.58));
    G.addEdge(DirectedEdge(6, 4, 0.93));

    DijkstraSP sp(&G, 0);
    cout << endl;
    for (int v = 0; v < G.vertices(); v++) {
        cout << "Desde 0" << " hasta " << v << "  d = " << sp.distTo(v) << ": " << endl << endl;;
        for (DirectedEdge e : sp.pathTo(v)) {
            cout << e.toString();
            cout << "(" << e.getWeight() << ")" << endl;
        }
        cout << std::endl;
    }
    return 0;
}

