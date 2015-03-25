#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>
#include "utils.hpp"
#include "graph.hpp"

class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph *, int);
    double distTo(int v) { return dist[v]; }
    std::vector<DirectedEdge> pathTo(int);
private:
    void relax(DirectedEdge);

    int s;
    double *dist;
    std::vector<DirectedEdge> edge;
    MinIndexedPQ pq;
};

#endif // SHORTEST_PATH_HPP
