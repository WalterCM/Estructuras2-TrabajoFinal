#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

const double PI = 3.14159265358979323846;

class Vertex
{
public:
    Vertex();
    Vertex(int, int);
    void draw(sf::RenderWindow *);

    sf::Vector2f getPosition()
    {
        sf::Vector2f position(x + radius, y + radius);
        return position;
    }

    float getX()    { return x + radius; }
    float getY()    { return y + radius; }

    int getValue()
    {
        return i;
    }

    int getRadius()
    {
        return radius;
    }
private:
    float x;
    float y;

    int i;

    static const int radius = 20;
    static constexpr float distCenter = 200;
    static const int charSize = 30;

    sf::CircleShape shape;
    sf::Font font;
    sf::Text text;
};


/*  Clase para las aristas dirigidas
 *      parametros:
 *      v = vertice inicial de la arista
 *      w = vertice final de la arista
 *      weight = peso de la arista (o distancia)
 */
class DirectedEdge
{
public:
    DirectedEdge(int, int, double);

    // Constructor. Inicializa los argumentos
    DirectedEdge(int, int, double, int);

    // Funcion que devuelve el vertice inicial
    int from()          { return v; }

    // Funcion que devuelve el vertice final
    int to()            { return w; }

    // Funcion que devuelve el peso
    double getWeight()  { return weight; }

    void createVertex(int);

    // Funcion que devuelve la arista como string
    std::string toString();

    void draw(sf::RenderWindow *);
    void draw(sf::RenderWindow *, sf::Color);
private:
    int v, w;
    double weight;
    Vertex vVertex, wVertex;
    sf::Texture texture;
    sf::Sprite sprite;
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
    int vertex();
    void draw(sf::RenderWindow *);

private:
    int v;
    int adjSize;
    std::list<DirectedEdge>  *adjacent;

    std::vector<Vertex> vertexShape;
};

typedef EdgeWeightedDigraph Graph;

#endif // GRAPH_HPP
