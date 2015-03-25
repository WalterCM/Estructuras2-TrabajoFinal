#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cstdlib>
#include "utils.hpp"
#include "graph.hpp"

/*  Implementacion del algoritmo de Dijkstra
 *  usando colas de prioridad
 *  parametros:
 *      G = El grafo en el que se correra el algoritmo
 *      s = El source, o la fuente de donde empezaran todos los caminos
*/
class DijkstraSP
{
public:
    // Constructor. Ademas de inicializar variables, realiza los calculos para hallar los caminos
    DijkstraSP(EdgeWeightedDigraph *, int);

    // Funcion que devuelve la distancia entre la fuenta y un vertice v
    double distTo(int v) { return dist[v]; }
    std::string distToString(int);

    // Funcion que devuelve el vector que contiene los adyacentes de un terminado sink
    std::list<DirectedEdge> pathTo(int);

    int getSource()     { return s; }
    std::string getSourceString();
private:
    // Funcion auxiliar qyue contiene el metodo de relajacion
    void relax(DirectedEdge);

    int s;                              // Source. Fuente del algoritmo o vertice inicial
    double *dist;                       // Arreglo de distancias desde la fuente
    std::vector<DirectedEdge> edge;     // Vector de aristas que se usara para formar los caminos
    MinIndexedPQ pq;                    // Cola de prioridad
};

#endif // SHORTEST_PATH_HPP
