#ifndef UTILS_HPP
#define UTILS_HPP

/*  Cola de prioridad indexada
 *  Es una cola de prioridad que es ordenada dependiendode unas llaves(leys)
 *  Ademas de que contiene indice o valores.
 *  parametros:
 *      NMAX = Maxima cantidad de elementos de la cola
*/
class MinIndexedPQ
{
public:
    // Constructor. Crea un MinIndexedPQ vacio el cual puede contener hasta NMAX elementos
    MinIndexedPQ(int);

    // Destructor. Elimina la cola despues de ser usada.
    ~MinIndexedPQ();

    // esta vacio?
    bool isEmpty() { return N == 0; }

    // es i parte del priority queue?
    bool contains(int i) { return index[i] != -1; }

    // asocia el key con el indice i; 0 < i < NMAX
    void insert(int i, int key);

    // elimina el key menor y retorna el indice asociado con el key en cuestion
    int deleteMin();

    // reduce el key asociado con el indice i hasta el valor especificado
    void decreaseKey(int i, int key);

private:
    void swap(int i, int j);

    void bubbleUp(int k);

    void bubbleDown(int k);

    int NMAX;
    int N;
    int *heap;
    int *index;
    int *keys;
};


#endif // UTILS_HPP
