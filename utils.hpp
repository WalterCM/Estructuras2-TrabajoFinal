#ifndef UTILS_HPP
#define UTILS_HPP

class MinIndexedPQ
{
public:
    // Crea un MinIndexedPQ vacio el cual puede contener hasta NMAX elementos
    MinIndexedPQ(int NMAX)
    {
        this->NMAX = NMAX;
        N = 0;
        keys = new int[NMAX + 1];
        heap = new int[NMAX + 1];
        index = new int[NMAX + 1];
        for (int i = 0; i <= NMAX; i++)
            index[i] = -1;
    }

    ~MinIndexedPQ()
    {
        delete [] keys;
        delete [] heap;
        delete [] index;
    }
    // esta vacio?
    bool isEmpty() { return N == 0; }

    // es i parte del priority queue?
    bool contains(int i) { return index[i] != -1; }

    // asocia el key con el indice i; 0 < i < NMAX
    void insert(int i, int key) {
        N++;
        index[i] = N;
        heap[N] = i;
        keys[i] = key;
        bubbleUp(N);
    }

    // elimina el key menor y retorna el indice asociado con el key en cuestion
    int deleteMin() {
        int min = heap[1];
        swap(1, N--);
        bubbleDown(1);
        index[min] = -1;
        heap[N + 1] = -1;
        return min;
    }

    // reduce el key asociado con el indice i hasta el valor especificado
    void decreaseKey(int i, int key)
    {
        keys[i] = key;
        bubbleUp(index[i]);
    }
private:
    // intercambia los valores
    void swap(int i, int j)
    {
        int t = heap[i];
        heap[i] = heap[j];
        heap[j] = t;
        index[heap[i]] = i; index[heap[j]] = j;
    }

    void bubbleUp(int k)
    {
        while (k > 1 && keys[heap[k / 2]] > keys[heap[k]]) {
            swap(k, k / 2);
            k = k / 2;
        }
    }

    void bubbleDown(int k)
    {
        int j;
        while(2 * k <= N) {
            j = 2 * k;
            if (j < N && keys[heap[j]] > keys[heap[j + 1]])
                j++;
            if (keys[heap[k]] <= keys[heap[j]])
                break;
            swap(k, j);
            k = j;
        }
    }

    int NMAX;
    int N;
    int *heap;
    int *index;
    int *keys;
};


#endif // UTILS_HPP
