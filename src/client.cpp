#include <iostream>
#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "shortest_path.hpp"

#include "constants.hpp"

using namespace std;

class Client
{
public:
    Client()
    {
        G = new Graph();
    }

    Client(int v)
    {
        G  = new Graph(v);
    }

    void startNewGraph()
    {
        spStarted = false;
        cout << "\n\tcuantos verticse desea que tenga el grafo?: " << endl;
        int v;
        prompt();
        cin >> v;
        G = new Graph(v);
    }

    void addEdge()
    {
        if (G->vertex() == 0 || G->vertex() == 1) {
            system("cls");
            cout << "\n\tError: No se puede agregar aristas. No hay suficientes vertices" << endl;
            wait();
            return;
        }
        cout << endl;
        cout << "\tEscriba el vertice inicial(0-" << G->vertex() - 1 <<"): ";
        int v;  cin >> v;
        if (v >= G->vertex()) {
            system("cls");
            cout << "\n\tError: No existe ese vertice en el grafo" << endl;
            wait();
            return;
        }

        cout << "\tEscriba el vertice final(0-" << G->vertex() - 1 <<"): ";
        int w;  cin >> w;
        if (w >= G->vertex()) {
            system("cls");
            cout << "\n\tError: No existe ese vertice en el grafo" << endl;
            wait();
            return;
        }

        cout << "\tEscriba el peso entre los vertices: ";
        double we; cin >> we;
        if (we < 0) {
            system("cls");
            cout << "\n\tError: No puede haber pesos negativos" << endl;
            wait();
            return;
        }
        G->addEdge(DirectedEdge(v, w, we, G->vertex()));
    }

    void startGUI()
    {
        if (G->vertex() > 0) {
            started = true;
            window.create(sf::VideoMode(WIDTH, HEIGHT), "Programa de Caminos Minimos!");
        } else {
            cout << "\n\tError: El grafo tiene muy pocos vertices" << endl;
            wait();
        }
    }

    void startDijkstra()
    {
         cout << "\n\tCual sera el vertice fuente?" << endl;
        int s;
        prompt();
        cin >> s;
        if (s < G->vertex()) {
            spStarted = true;
            sp = new DijkstraSP(G, s);
        } else {
            system("cls");
            cout << "\n\tError: No existe ese vertice" << endl;
            wait();
        }
    }

    void shortestPath()
    {
        if (!spStarted) {
            system("cls");
            cout << "\tERROR: No se ha iniciado el algoritmo de Dijkstra" << endl;
            return;
        } else {
            shortP = true;
            cout << "\n\tEscriba el vertice cuyo camino mas corto desea hallar" << endl;
            prompt();
            cin >> sink;
        }
    }

    bool isWindowOpen()
    {
        return window.isOpen();
    }

    bool isGUIStarded()
    {
        return started;
    }

    void draw()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        G->draw(&window);
        if (spStarted) {
            for (int i = 0; i < G->vertex(); i++) {
                for (DirectedEdge e : sp->pathTo(i))
                    e.draw(&window, sf::Color::Yellow);
            }
        }

        if (spStarted && shortP) {
            for (DirectedEdge e : sp->pathTo(sink))
                e.draw(&window, sf::Color::Red);

        }
        window.display();
    }

    void input()
    {
        int op;
        op = menu();
        switch (op) {
        case 1:
            startNewGraph();
            break;
        case 2:
            addEdge();
            break;
        case 3:
            startDijkstra();
            break;
        case 4:
            shortestPath();
            break;
        case 5:
            G = new Graph(8);
            G->addEdge(DirectedEdge(0, 1, 5.0, G->vertex()));
            G->addEdge(DirectedEdge(0, 4, 9.0, G->vertex()));
            G->addEdge(DirectedEdge(0, 7, 8.0, G->vertex()));
            G->addEdge(DirectedEdge(1, 2, 12.0, G->vertex()));
            G->addEdge(DirectedEdge(1, 3, 15.0, G->vertex()));
            G->addEdge(DirectedEdge(1, 7, 4.0, G->vertex()));
            G->addEdge(DirectedEdge(2, 3, 3.0, G->vertex()));
            G->addEdge(DirectedEdge(2, 6, 11.0, G->vertex()));
            G->addEdge(DirectedEdge(3, 6, 9.0, G->vertex()));
            G->addEdge(DirectedEdge(4, 5, 4.0, G->vertex()));
            G->addEdge(DirectedEdge(4, 6, 20.0, G->vertex()));
            G->addEdge(DirectedEdge(4, 7, 5.0, G->vertex()));
            G->addEdge(DirectedEdge(5, 2, 1.0, G->vertex()));
            G->addEdge(DirectedEdge(5, 6, 13.0, G->vertex()));
            G->addEdge(DirectedEdge(7, 5, 6.0, G->vertex()));
            G->addEdge(DirectedEdge(7, 2, 7.0, G->vertex()));

            cout << "\n\tTest ejecutado correctamente" << endl;
            wait();
            break;
        case 6:
            startGUI();
            break;
        case 7:
            window.close();
            break;
        case 8:
            exit(0);
        default:
            break;
        }
    }
protected:
private:
    void prompt()
    {
        cout << "\n\t>> ";
    }

    int menu()
    {
        system("cls");
        cout << "\tCaminos minimos" << endl;
        cout << "\n\t1. Creat nuevo grafo." << endl;
        cout << "\t2. Agregar nueva arista." << endl;
        cout << "\t3. Dijkstra." << endl;
        cout << "\t4. Generar el camino mas corto a un mismo vertice." << endl;
        cout << "\t5. Ejecutar test." << endl;
        cout << "\t6. Mostrar GUI." << endl;
        cout << "\t7. Cerrar  GUI." << endl;
        cout << "\t8. Salir." << endl;
        int op;
        prompt();
        cin >> op;
        return op;
    }

    void wait()
    {
        cout << "\n\tPersione <Enter> para continuar." << endl;
        cin.clear();
        cin.ignore(255, '\n');
        cin.get();
    }

    Graph *G;
    DijkstraSP *sp;

    sf::RenderWindow window;
    bool started = false;
    bool spStarted = false;
    bool shortP = false;
    int sink = 0;
    static const int WIDTH = 800;
    static const int HEIGHT = 600;
};

int main()
{
    cout << "\tCaminos minimos" << endl;
    Client *c = new Client();

    while (1) {
        if (c->isGUIStarded())
            c->draw();
        c->input();

    }
}
