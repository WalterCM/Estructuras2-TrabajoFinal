#include <iostream>
#include <fstream>
#include <sstream>
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

        // String que se usara para el mensaje de salida
        string out = "";

        // Dibuja el arbol generador de color amarillo
        if (spStarted) {

            for (int i = 0; i < G->vertices(); i++) {
                ostringstream  ss;
                ss << i;
                out += "Desde " + sp->getSourceString() + " hasta " + ss.str() +
                        "\td = " + sp->distToString(i) + "\n";
                for (DirectedEdge e : sp->pathTo(i))
                    cout << "\t" << e.toString();

                cout << endl<< endl;

                for (DirectedEdge e : sp->pathTo(i)) {
                    e.draw(&window, sf::Color::Yellow);
                    out +=e.toString() + " ";
                }
                out += "\n\n";
            }
        }

        // Dibuja el camino mas corto hacia otro punto de color rojo
        if (spStarted && shortP) {
            for (DirectedEdge e : sp->pathTo(sink))
                e.draw(&window, sf::Color::Red);
        }
        title.setFont(font);
        window.draw(title);

        credits.setFont(font);
        window.draw(credits);

        output.setFont(font);
        output.setString(out);
        window.draw(output);
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
        shortP = false;
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
        if (G->vertices() == 0 || G->vertices() == 1) {
            system("cls");
            cout << "\n\tError: No se puede agregar aristas. No hay suficientes vertices" << endl;
            wait();
            return;
        }
        cout << endl;
        cout << "\tEscriba el vertice inicial(0-" << G->vertices() - 1 <<"): ";
        int v;  cin >> v;
        if (v >= G->vertices()) {
            system("cls");
            cout << "\n\tError: No existe ese vertice en el grafo" << endl;
            wait();
            return;
        }

        cout << "\tEscriba el vertice final(0-" << G->vertices() - 1 <<"): ";
        int w;  cin >> w;
        if (w >= G->vertices()) {
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
        G->addEdge(DirectedEdge(v, w, we, G->vertices()));
    }

    // Funcion que inicia la interfax grafica de usuario
    void startGUI()
    {
        if (G->vertices() > 0) {
            startedGUI = true;
            window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Programa de Caminos Minimos!");

            font.loadFromFile(FONT_FILE);

            title.setCharacterSize(TITLE_CHAR_SIZE);
            title.setColor(sf::Color::White);
            title.setPosition(TITLE_POS_X, TITLE_POS_Y);
            title.setString("Caminos minimos (Dijkstra)");

            credits.setCharacterSize(CREDITS_CHAR_SIZE);
            credits.setColor(sf::Color::White);
            credits.setPosition(CREDITS_POS_X, CREDITS_POS_Y);
            string crStr = "CREDITOS:\tCapa Macedo, Walter";
            crStr += "\n\t\t\t\t\t\tChallhua Reynoso, Jefferson";
            crStr += "\n\t\t\t\t\t\tQuintana Vasquez, Alez Alberto";
            credits.setString(crStr);

            output.setCharacterSize(OUTPUT_CHAR_SIZE);
            output.setColor(sf::Color::White);
            output.setPosition(OUTPUT_POS_X, OUTPUT_POS_Y);
        } else {
            cout << "\n\tError: El grafo tiene muy pocos vertices" << endl;
            wait();
        }
    }

    // Funcion que inicia el algoritmo de Dijkstra
    void startDijkstra()
    {
        if (G->vertices() == 0) {
            cout << "\n\tError: El grafo no tiene vertices" << endl;
            wait();
            return;
        }
        cout << "\n\tCual sera el vertice fuente?" << endl;
        int s;
        prompt();
        cin >> s;
        if (s < G->vertices()) {
            spStarted = true;
            sp = new DijkstraSP(G, s);
        } else {
            cout << "\n\tError: No existe ese vertice" << endl;
            wait();
        }

        if (!startedGUI) {

            char a;

            do {
                cout << "\n\tDesea visualizar el arbol de caminos cortos?(Y/N)" << endl;
                prompt();
                cin >> a;
                a = toupper(a);
                if (a == 'N') return;
                if (a != 'Y') cout << "\n\tERROR: Solo se permiten Y, y, N, n" << endl;
            } while (a != 'Y');

            for (int i = 0; i < G->vertices(); i++) {
                cout << "\n\tDesde " << s << " hasta " << i << "\t\td = ";
                if (sp->distTo(i) == INFINITY)
                    cout << "INFINITO:" << endl;
                else
                    cout << sp->distTo(i) << endl;
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
            cout << "\tERROR: No se ha iniciado el algoritmo de Dijkstra aun" << endl;
            return;
        } else {
            shortP = true;
            cout << "\n\tEscriba el vertice cuyo camino mas corto desea hallar" << endl;
            prompt();
            cin >> sink;
        }

        if (!startedGUI) {
            cout << "\n\tDesde " << sp->getSource() << " hasta " << sink << "\t\td = " << sp->distTo(sink) << endl;
            for (DirectedEdge e : sp->pathTo(sink))
                cout << "\t" << e.toString();
            cout << endl;
            wait();
        }
    }

    void executeTest()
    {
        system("cls");
        cout << "\n\tEscoja el test que desea ejecutar." << endl;
        cout << "\n\t1. test1.txt  (5 vertices, 6 aristas)" << endl;
        cout << "\t2. test2.txt  (8 vertices, 15 aristas)" << endl;
        cout << "\t3. test3.txt  (8 vertices, 16 aristas)" << endl;
        cout << "\t4. test4.txt  (10 vertices, 26 aristas)" << endl;

        prompt();
        int op;     cin >> op;

        switch (op) {
        case 1:
            createGraphFromFile("tests/test1.txt");
            break;
        case 2:
            createGraphFromFile("tests/test2.txt");
            break;
        case 3:
            createGraphFromFile("tests/test3.txt");
            break;
        case 4:
            createGraphFromFile("tests/test4.txt");
            break;
        case 5:
            createGraphFromFile("tests/test5.txt");
            break;
        default:
            break;
        }
        cout << "\n\tEl test ha sido ejecutado correctamente" << endl;
        wait();
    }

    void createGraphFromFile(string file)
    {
        spStarted = false;
        shortP = false;
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
                G->addEdge(DirectedEdge(v, w, we, G->vertices()));
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
        cout << "\n\t1. Creat nuevo grafo" << endl;
        cout << "\t2. Agregar nueva arista" << endl;
        cout << "\t3. Ejecutar tes." << endl;
        cout << "\t4. Crear un grafo desde un archivo de texto" << endl;
        cout << "\t5. Dijkstra" << endl;
        cout << "\t6. Generar el camino mas corto a un unico vertice" << endl;
        cout << "\t7. Mostrar GUI" << endl;
        cout << "\t8. Cerrar  GUI" << endl;
        cout << "\t9. Salir" << endl;
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
    sf::Font font;
    sf::Text title;
    sf::Text output;
    sf::Text credits;

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
