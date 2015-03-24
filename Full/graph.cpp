#include "graph.hpp"
using namespace std;
Vertex::Vertex() {}

Vertex::Vertex(int i, int v)
{
    this->i = i;
    shape.setRadius(radius);

    x = 400 + distCenter * cos(2 * PI * i / v) - radius;
    y = 300 + distCenter * sin(2 * PI * i / v) - radius;
    if (v == 1) {
        x = 400 - radius;
        y = 300 - radius;
    }

    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);

    if (!font.loadFromFile("arial.ttf")) {
        cout << "Not loading" << endl;
        std::exit(-1);
    }

    std::ostringstream  ss;
    ss << i;
    std::string is = " " + ss.str();
    text.setString(is);

    text.setCharacterSize(charSize);
    text.setColor(sf::Color::Black);
    text.setPosition(x + 3, y);
}

void Vertex::draw(sf::RenderWindow *window)
{
    (*window).draw(shape);
    text.setFont(font);
    (*window).draw(text);
}

DirectedEdge::DirectedEdge(int v, int w, double weight)
{
    this->v = v;
    this->w = w;
    this->weight = weight;
}

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

    texture.loadFromFile("arrow.png");
    sprite.setPosition(vVertex.getPosition());
    const float d1 = 0.5;
    double angleInt = 2.0 * PI * abs(v - w) / amount;
    double scale = d1 * 2 * sin(angleInt / 2);

    sprite.scale(sf::Vector2f(scale, d1));
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

EdgeWeightedDigraph::EdgeWeightedDigraph(int v)
{
    this->v = v;
    adjacent = new std::list<DirectedEdge>[v];

    for (int i = 0; i < v; i++) {
        vertexShape.push_back(Vertex(i, v));
    }
}

void EdgeWeightedDigraph::addEdge(DirectedEdge e)
{
    int v = e.from();
    adjacent[v].push_back(e);
    adjSize++;
}

std::list<DirectedEdge> EdgeWeightedDigraph::adj(int index)
{
    return adjacent[index];
}

int EdgeWeightedDigraph::vertex()
{
    return v;
}

void EdgeWeightedDigraph::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < v; i++)
        for (DirectedEdge e : adjacent[i])
            e.draw(window);

    for (int i = 0; i < v; i++)
        vertexShape[i].draw(window);
}
