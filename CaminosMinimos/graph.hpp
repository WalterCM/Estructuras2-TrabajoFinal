#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <list>

/*  Clase para las aristas dirigidas
 *      parametros:
 *      v = vertice inicial de la arista
 *      w = vertice final de la arista
 *      weight = peso de la arista (o distancia)
 */
class DirectedEdge
{
public:
    // Constructor. Inicializa los argumentos
    DirectedEdge(int, int, double);

    // Funcion que devuelve el vertice inicial
    int from()          { return v; }

    // Funcion que devuelve el vertice final
    int to()            { return w; }

    // Funcion que devuelve el peso
    double getWeight()  { return weight; }

    // Funcion que devuelve la arista como string
    std::string toString();
private:
    int v, w;
    double weight;
};

/*  Clase para los grafos directos con arista pesada
 *  parametros:
 *      v = cantidad de vertices
 *      adjacent = arreglo de listas. Representa las aristas por cada vertice
*/
class EdgeWeightedDigraph
{
public:
    // Constructor. Inicializa los argumentos
    EdgeWeightedDigraph(int);

    // Destructor. Elimina el grafo tras ser usado.
    ~EdgeWeightedDigraph() { delete adjacent; }

    // Funcion que agrega unanueva arista de tipo "DirectedEdge" al grafo.
    void addEdge(DirectedEdge);

    // Funcion que devuelve la lista con las conexion de un solo vertice.
    // Es usada para iterar por las aristas de un mismo vertice
    std::list<DirectedEdge> adj(int);

    // Funcino que devuelve la cantidad de vertices
    int vertices();
private:
    int v;
    std::list<DirectedEdge>  *adjacent;
};

typedef EdgeWeightedDigraph Graph;

// Test client a
//int main()
//{
//    Graph G(5);
//    G.addEdge(DirectedEdge(1, 2, 1.3));
//    G.addEdge(DirectedEdge(1, 3, 2));
//    G.addEdge(DirectedEdge(1, 5, 4));
//    G.addEdge(DirectedEdge(1, 6, 3.1));
//    G.addEdge(DirectedEdge(2, 3, 1));
//    for (DirectedEdge e : G.adj(2)) {
//        std::cout << e.from() << " -> ";
//        std::cout << e.to() << " peso: " << e.getWeight();
//        std::cout << std::endl;
//    }
//}

#endif // GRAPH_HPP
