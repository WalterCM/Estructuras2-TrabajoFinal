
#ifndef DIRECTED_EDGE_HPP
#define DIRECTED_EDGE_HPP

#include "vertex.hpp"

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
    DirectedEdge(int, int, double, int);

    // Funcion que devuelve el vertice inicial
    int from()          { return v; }

    // Funcion que devuelve el vertice final
    int to()            { return w; }

    // Funcion que devuelve el peso
    double getWeight()  { return weight; }

    // Funcion que devuelve la arista como string
    std::string toString();

    // Funcion que dibuja una determinada arista
    void draw(sf::RenderWindow *);

    // Funcionq ue dibuja una determinada arista y ademas, la pinta
    void draw(sf::RenderWindow *, sf::Color);
private:
    int v, w;                       // Vertices inicial y final
    double weight;                  // Peso de la arista
    Vertex vVertex, wVertex;        // Objetos de la clase que controla los vertices
    sf::Texture texture;            // Objeto que guarda la imagen de la flecha
    sf::Sprite sprite;              // Objeto que guarda el sprite de las aristas
};

#endif // DIRECTED_EDGE_HPP
