
#include <sstream>

#include "directed_edge.hpp"
#include "constants.hpp"

DirectedEdge::DirectedEdge(int v, int w, double weight, int amount) : vVertex(v, amount), wVertex(w, amount)
{
    this->v = v;
    this->w = w;
    this->weight = weight;

    float vx = vVertex.getX();
    float vy = vVertex.getY();

    float wx = wVertex.getX();
    float wy = wVertex.getY();

    float m = 0.0;
    double angle = 0.0;

    // Calculos para determinar el angulo que tomara la arista en la pantalla
    if (wx == vx && (wy - vy) > 0)
        angle = 90;
    else
        m = (wy - vy) / (wx - vx);

    if (wx == vx && (wy - vy) < 0)
        angle = -90;
    else if ((wy - vy) < 0 && (wx - vx) < 0)
        angle = 180 + atan(m) * 180 / PI;
    else if ((wy - vy) < 0 && (wx - vx) > 0)
        angle = atan(m) * 180 / PI;
    else if ((wy - vy) >= 0 && (wx - vx) < 0)
        angle = 180 + atan(m) * 180 / PI;
    else if ((wy - vy) > 0 && (wx - vx) > 0)
        angle = atan(m) * 180 / PI;

    // Carga la textura de la flecha para las aristas
    texture.loadFromFile("Content/arrow.png");

    // Configura la posicion inicial de la flecha
    sprite.setPosition(vVertex.getPosition());

    const float d1 = 0.5;
    double angleInt = 2.0 * PI * abs(v - w) / amount;
    double scale = d1 * 2 * sin(angleInt / 2);

    // Escala al vector basado en una formula para hallar diagonales de un poligoono regular
    sprite.scale(sf::Vector2f(scale, d1));

    // Rota el sprite basado en el angulo hallado anteriormente
    sprite.rotate(angle);
}

std::string DirectedEdge::toString()
{
    std::ostringstream  ss;
    ss << v;
    std::string vs = ss.str();
    std::ostringstream  ss2;
    ss2 << w;
    std::string vw = ss2.str();
    return vs + " -> " + vw + " ";
}

void DirectedEdge::draw(sf::RenderWindow *window)
{
    sprite.setTexture(texture);
    (*window).draw(sprite);
}

void DirectedEdge::draw(sf::RenderWindow *window, sf::Color color)
{
    sprite.setTexture(texture);
    sprite.setColor(color);
    (*window).draw(sprite);
}
