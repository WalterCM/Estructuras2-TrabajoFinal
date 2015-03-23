class MinIndexedPQ
{
public:
    // Create an empty MinIndexedPQ which can contain atmost NMAX elements
    MinIndexedPQ(int NMAX)
    {
        this->NMAX = NMAX;
        N = 0;
        keys = new int[NMAX + 1];
        heap = new int[NMAX + 1];
        index = new int[NMAX + 1];
        for(int i = 0; i <= NMAX; i++)
        index[i] = -1;
    }

    ~MinIndexedPQ()
    {
        delete [] keys;
        delete [] heap;
        delete [] index;
    }
    // check if the PQ is empty
    bool isEmpty() { return N == 0; }

    // check if i is an index on the PQ
    bool contains(int i) { return index[i] != -1; }

    // associate key with index i; 0 < i < NMAX
    void insert(int i, int key) {
        N++;
        index[i] = N;
        heap[N] = i;
        keys[i] = key;
        bubbleUp(N);
    }

    // delete the minimal key and return its associated index
    // Warning: Don't try to read from this index after calling this function
    int deleteMin() {
        int min = heap[1];
        swap(1, N--);
        bubbleDown(1);
        index[min] = -1;
        heap[N + 1] = -1;
        return min;
    }

    // decrease the key associated with index i to the specified value
    void decreaseKey(int i, int key)
    {
        keys[i] = key;
        bubbleUp(index[i]);
    }
private:
    int NMAX, N, *heap, *index, *keys;
    void swap(int i, int j)
    {
        int t = heap[i]; heap[i] = heap[j]; heap[j] = t;
        index[heap[i]] = i; index[heap[j]] = j;
    }

    void bubbleUp(int k)
    {
        while(k > 1 && keys[heap[k / 2]] > keys[heap[k]]) {
            swap(k, k / 2);
            k = k / 2;
        }
    }

    void bubbleDown(int k)
    {
        int j;
        while(2 * k <= N) {
            j = 2 * k;
            if(j < N && keys[heap[j]] > keys[heap[j + 1]])
            j++;
            if(keys[heap[k]] <= keys[heap[j]])
            break;
            swap(k, j);
            k = j;
        }
    }
};
