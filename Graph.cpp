#include <iostream>
#include <string>
#include <list>

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
    DirectedEdge(int v, int w, double weight)
    {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    // Funcion que devuelve el vertice inicial
    int from()
    { return v; }

    // Funcion que devuelve el vertice final
    int to()
    { return w; }

    // Funcion que devuelve el peso
    double getWeight()
    { return weight; }

    // Funcion que devuelve la arista como string
    std::string toString()
    {
        //TODO: Devolver la version string de la arista
        return "";
    }
protected:
private:
    int v, w;
    double weight;
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
    EdgeWeightedDigraph(int v)
    {
        this->v = v;
        adjacent = new std::list<DirectedEdge>[v];
    }

    // Destructor. Elimina el grafo tras ser usado.
    ~EdgeWeightedDigraph()
    {
        delete adjacent;
    }

    // Funcion que agrega unanueva arista de tipo "DirectedEdge" al grafo.
    void addEdge(DirectedEdge e)
    {
        int v = e.from();
        adjacent[v].push_back(e);
    }

    // Funcion que devuelve la lista con las conexion de un solo vertice.
    // Es usada para iterar por las aristas de un mismo vertice
    std::list<DirectedEdge> adj(int index)
    {
        return adjacent[index];
    }

    // Funcino que devuelve la cantidad de vertices
    int vertex()
    {
        //TODO: Agregar la funcion que devuelve la cantidad de vertices
        return 0;
    }
protected:
private:
    int v;
    std::list<DirectedEdge>  *adjacent;
};

typedef EdgeWeightedDigraph Graph;

// Test client a
int main()
{
    Graph G(5);
    G.addEdge(DirectedEdge(1, 2, 1.3));
    G.addEdge(DirectedEdge(1, 3, 2));
    G.addEdge(DirectedEdge(1, 5, 4));
    G.addEdge(DirectedEdge(1, 6, 3.1));
    for (DirectedEdge e : G.adj(1)) {
        std::cout << e.from() << " -> ";
        std::cout << e.to() << " peso: " << e.getWeight();
        std::cout << std::endl;
    }
}
