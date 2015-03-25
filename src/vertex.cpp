#include <sstream>

#include "vertex.hpp"
#include "constants.hpp"

/*Vertex*/
// Constructor que recibe el indice del vertice y la cantidad de vertices
Vertex::Vertex(int iindex, int v)
{
    this->i = iindex;
    shape.setRadius(RADIUS);

    x = WINDOW_WIDTH / 2 + DIST_CENTER * cos(2 * PI * i / v) - RADIUS;
    y = WINDOW_HEIGHT / 2 + DIST_CENTER * sin(2 * PI * i / v) - RADIUS;
    if (v == 1) {
        x = WINDOW_WIDTH / 2 - RADIUS;
        y = WINDOW_HEIGHT / 2 - RADIUS;
    }

    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);

    if (!font.loadFromFile(FONT_FILE)) {
        std::exit(-1);
    }

    std::ostringstream  ss;
    ss << i;
    std::string is = " " + ss.str();
    text.setString(is);

    text.setCharacterSize(CHAR_SIZE);
    text.setColor(sf::Color::Black);
    text.setPosition(x + 3, y);
}

void Vertex::draw(sf::RenderWindow *window)
{
    (*window).draw(shape);
    text.setFont(font);
    (*window).draw(text);
}

sf::Vector2f Vertex::getPosition()
{
    sf::Vector2f position(x + RADIUS, y + RADIUS);
    return position;
}

float Vertex::getX()    { return x + RADIUS; }
float Vertex::getY()    { return y + RADIUS; }
