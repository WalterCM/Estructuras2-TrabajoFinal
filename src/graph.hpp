#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constants.hpp"

const double PI = 3.14159265358979323846;       // Constante del numero PI

/*  Clase para los vertices del grafo
 *      parametros:
 *      i = indice que indica el numero de vertice
 *      v = cantidad de verticse en el grafo
 */
class Vertex
{
public:
    // Constructor por defecto de la clase
    Vertex() {}

    // Constructor que recibe el indice del vertice y la cantidad de vertices
    Vertex(int, int);

    // Funcion que dibuja el vertice en la pantalla
    void draw(sf::RenderWindow *);

    // Funcion que devuelve el vector posicion del vertice
    sf::Vector2f getPosition();

    float getX()    { return x + RADIUS; }      // Posicion real en x
    float getY()    { return y + RADIUS; }      // Posicion real en y

    // Funcion que devuelve el valor o numero de vertice
    int getValue()                              { return i; }

    // Funcion que devuelve el radio del vertice
    int getRadius()                             { return RADIUS; }
private:
    float x;                                    // Posicion en el eje x
    float y;                                    // Posicion en el eje y

    int i;                                      // Numero de vertice



    sf::CircleShape shape;                      // Objeto que guarda la forma del vertice
    sf::Font font;                              // Fuente de los numeros en los vertices
    sf::Text text;                              // Los numeros en los vertices
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
    int vertex();

    // Funcion que grafica los vectores de un grafo y sus aristas
    void draw(sf::RenderWindow *);

    // Destructor. Elimina el grafo tras ser usado.
    ~EdgeWeightedDigraph() { delete adjacent; }
private:
    int v;                                  // Cantidad de vertices
    std::list<DirectedEdge>  *adjacent;     // Arreglo de listas de adyacentes
    std::vector<Vertex> vertexShape;        // Vector con la forma grafica de lo vectores
};

typedef EdgeWeightedDigraph Graph;

#endif // GRAPH_HPP
