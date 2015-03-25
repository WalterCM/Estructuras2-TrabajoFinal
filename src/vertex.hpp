
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <SFML/Graphics.hpp>


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

    float getX();                               // Posicion real en x
    float getY();                               // Posicion real en y

    // Funcion que devuelve el valor o numero de vertice
    int getValue()                              { return i; }
private:
    float x;                                    // Posicion en el eje x
    float y;                                    // Posicion en el eje y

    int i;                                      // Numero de vertice

    sf::CircleShape shape;                      // Objeto que guarda la forma del vertice
    sf::Font font;                              // Fuente de los numeros en los vertices
    sf::Text text;                              // Los numeros en los vertices
};

#endif // VERTEX_HPP
