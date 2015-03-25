
#ifndef EDGE_WEIGHTED_GRAPH_HPP
#define EDGE_WEIGHTED_GRAPH_HPP

#include <list>

#include "directed_edge.hpp"

/*  Clase para los grafos directos con arista pesada
 *  parametros:
 *      v = cantidad de vertices
 *      adjacent = arreglo de listas. Representa las aristas por cada vertice
*/
class EdgeWeightedDigraph
{
public:
    // Constructor por defecto
    EdgeWeightedDigraph() {}

    // Constructor. Inicializa los argumentos
    EdgeWeightedDigraph(int);

    // Crea un nuevo grafo. Recibe como argumento la cantidad de elementos.
    void createGraph(int);

    // Funcion que agrega unanueva arista de tipo "DirectedEdge" al grafo.
    void addEdge(DirectedEdge);

    // Funcion que devuelve la lista con las conexion de un solo vertice.
    // Es usada para iterar por las aristas de un mismo vertice
    std::list<DirectedEdge> adj(int);

    // Funcino que devuelve la cantidad de vertices
    int vertices();

    // Funcion que grafica los vectores de un grafo y sus aristas
    void draw(sf::RenderWindow *);

    // Destructor. Elimina el grafo tras ser usado.
    ~EdgeWeightedDigraph() { delete adjacent; }
private:
    int v;                                  // Cantidad de vertices
    std::list<DirectedEdge>  *adjacent;     // Arreglo de listas de adyacentes
    std::vector<Vertex> vertexShape;        // Vector con la forma grafica de lo vectores
};

#endif // EDGE_WEIGHTED_GRAPH_HPP
