#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "shortest_path.hpp"

using namespace std;

int main()
{
    int x;
    cout << "hola" << endl;
    cin >> x;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Programa de Caminos Minimos!");

    Graph G(10);
    for (int i = 0; i < G.vertex(); i++) {
        for (int j = 0; j < G.vertex(); j++) {
            if (i != j)
                G.addEdge(DirectedEdge(i, j, 1, G.vertex()));
        }
    }

    DijkstraSP sp(&G, 0);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        G.draw(&window);
//        for (int i = 0; i < G.vertex(); i++) {
//            for (DirectedEdge e : sp.pathTo(i)) {
//                e.draw(&window, sf::Color::Red);
//            }
//        }
        window.display();
    }
}
