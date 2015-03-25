#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "graph.hpp"
#include "shortest_path.hpp"

#include "constants.hpp"

using namespace std;

class Client
{
public:
    // Crea un grafo vacio
    Client()        { G = new Graph(0); }

    // Crea un grafo con v vertices
    Client(int v)   { G  = new Graph(v); }

    // Funcion que dibuja los grafos, los vertices, las aristas y los caminos mas cortos
    void draw()
    {
        // Objeto de la clase Event para controlar los eventos de cerrado de ventana
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Si se hace click en cerrar, la ventana se cierra
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpia la pantalla y la pinta el fondo de color negro
        window.clear(sf::Color::Black);
        // Dibuja el grafo entero
        G->draw(&window);

        // Dibuja el arbol generador de color amarillo
        if (spStarted) {
            for (int i = 0; i < G->vertex(); i++) {
                for (DirectedEdge e : sp->pathTo(i))
                    e.draw(&window, sf::Color::Yellow);
            }
        }

        // Dibuja el camino mas corto hacia otro punto de color rojo
        if (spStarted && shortP) {
            for (DirectedEdge e : sp->pathTo(sink))
                e.draw(&window, sf::Color::Red);
        }
        window.display();
    }

    // Muestra el menu, captura las opciones escogidas y realiza las acciones deseadas
    void input()
    {
        int op;
        op = menu();
        switch (op) {
        case 1:                     // Crear nuevo grafo
            startNewGraph();
            break;
        case 2:                     // Agregar arista
            addEdge();
            break;
        case 3:                     // Ejecutar tests
            executeTest();
            break;
        case 4: {                   // Crear un grafo desde un archivo de texto
            cout << "\n\tEscriba el nombre del archivo de texto";
            prompt();
            string file;
            cin >> file;
            createGraphFromFile(file);
            break;  }
        case 5:                     // Iniciar el algoritmo de Dijkstra
            startDijkstra();
            break;
        case 6:                     // Calcular camino mas corto
            shortestPath();
            break;
        case 7:                     // Iniciar la interfax grafica de usuario
            startGUI();
            break;
        case 8:                     // Finalizar la interfax grafica de usuario
            window.close();
            break;
        case 9:                     // Salir del programa completamente
            exit(0);
        default:
            break;
        }
    }

    bool isWindowOpen() { return window.isOpen();   }       // Devuelve true si la ventana esta abierta y false si esta cerrada
    bool isGUIStarded() { return startedGUI;           }       // Devuelve true si el GUI ha sido inicializado y false si es que no

private:
        // Funcion que inicia un pregunta por la cantidad de vertices e inicia un nuevo grafo
    void startNewGraph()
    {
        spStarted = false;
        int v = -1;
        do {
            cout << "\n\tcuantos verticse desea que tenga el grafo?: " << endl;
            prompt();
            cin >> v;
            if (v < 0)  cout << "\n\tERROR: El numero de grafos no puede ser negativo." << endl;
        } while (v < 0);

        G = new Graph(v);
    }

    // Funcion que pregunta por los vertices y el peso para formar una arista, y la agrega al grafo
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

    // Funcion que inicia la interfax grafica de usuario
    void startGUI()
    {
        if (G->vertex() > 0) {
            startedGUI = true;
            window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Programa de Caminos Minimos!");
        } else {
            cout << "\n\tError: El grafo tiene muy pocos vertices" << endl;
            wait();
        }
    }

    // Funcion que inicia el algoritmo de Dijkstra
    void startDijkstra()
    {
        if (G->vertex() == 0) {
            cout << "\n\tError: El grafo no tiene vertices" << endl;
            wait();
            return;
        }
        cout << "\n\tCual sera el vertice fuente?" << endl;
        int s;
        prompt();
        cin >> s;
        if (s < G->vertex()) {
            spStarted = true;
            sp = new DijkstraSP(G, s);
        } else {
            cout << "\n\tError: No existe ese vertice" << endl;
            wait();
        }

        if (!startedGUI) {
            for (int i = 0; i < G->vertex(); i++) {
                cout << "\tDesde " << s << " hasta " << i << ": " << endl;
                for (DirectedEdge e : sp->pathTo(i))
                    cout << "\t" << e.toString();

                cout << endl<< endl;
            }
            wait();
        }
    }

    // Funcion que calcula el camino mas corto desde la fuente hacia un determinado vertice
    void shortestPath()
    {
        if (!spStarted) {
            cout << "\tERROR: No se ha iniciado el algoritmo de Dijkstra" << endl;
            return;
        } else {
            shortP = true;
            cout << "\n\tEscriba el vertice cuyo camino mas corto desea hallar" << endl;
            prompt();
            cin >> sink;
        }
    }

    void executeTest()
    {
        system("cls");
        cout << "\n\tEscoja el test que desea correr." << endl;
        cout << "\n\t1. test1.txt" << endl;
        cout << "\t2. test2.txt" << endl;

        prompt();
        int op;     cin >> op;

        switch (op) {
        case 1:
            createGraphFromFile("tests/test1.txt");
            break;
        case 2:
            createGraphFromFile("tests/test2.txt");
            break;
        default:
            break;
        }
        cout << "\n\tEl test ha sido ejecutado correctamente" << endl;
        wait();
    }

    void createGraphFromFile(string file)
    {
        ifstream graphFile(file);

        int v, w;
        double we;
        int edgeNum;
        if (graphFile.is_open()) {
            graphFile >> v;
            G = new Graph(v);

            graphFile >> edgeNum;
            for (int i = 0; i < edgeNum; i++) {
                graphFile >> v >> w >> we;
                G->addEdge(DirectedEdge(v, w, we, G->vertex()));
            }
            graphFile.close();
        } else {
            cout << "\n\tNo se pudo abrir el archivo especificado." << endl;
        }
    }

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
        cout << "\t3. Ejecutar test." << endl;
        cout << "\t4. Crear un grafo desde un archivo de texto." << endl;
        cout << "\t5. Dijkstra." << endl;
        cout << "\t6. Generar el camino mas corto a un mismo vertice." << endl;
        cout << "\t7. Mostrar GUI." << endl;
        cout << "\t8. Cerrar  GUI." << endl;
        cout << "\t9. Salir." << endl;
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
    bool startedGUI = false;
    bool spStarted = false;
    bool shortP = false;
    int sink = 0;
};

int main()
{
    Client *c = new Client();

    while (1) {
        if (c->isGUIStarded())
            c->draw();
        c->input();

    }
}
