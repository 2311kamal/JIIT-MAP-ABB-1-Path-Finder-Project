#include <iostream>
#include <climits>
// #include <vector>
using namespace std;

#define v 9

template <typename T>
class vector
{

    // arr is the integer pointer
    // which stores the address of our vector
    T *arr;

    // capacity is the total storage
    // capacity of the vector
    int capacity;

    // current is the number of elements
    // currently present in the vector
    int current;

public:
    // Default constructor to initialise
    // an initial capacity of 1 element and
    // allocating storage using dynamic allocation
    vector()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }

    vector(int c, int val = 0)
    {
        arr = new T[c];
        for (int i = 0; i < c; i++)
        {
            arr[i] = val;
        }
        capacity = c;
        current = 0;
    }
    // destructor to deallocate storage allocated by dynamic allocation

    ~vector()
    {
        delete[] arr;
    }

    // Function to add an element at the last
    void push(T data)
    {

        // if the number of elements is equal to the
        // capacity, that means we don't have space to
        // accommodate more elements. We need to double the
        // capacity
        if (current == capacity)
        {
            T *temp = new T[2 * capacity];

            // copying old array elements to new array
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }

            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        // Inserting data
        arr[current] = data;
        current++;
    }

    // function to add element at any index
    void push(T data, int index)
    {

        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }

    // function to extract element at any index
    T get(int index)
    {

        // if index is within the range
        if (index < current)
            return arr[index];
    }

    // function to delete last element
    void pop()
    {
        current--;
    }

    // function to get size of the vector
    int size()
    {
        return current;
    }

    // function to get capacity of the vector
    int getcapacity()
    {
        return capacity;
    }

    // function to print array elements
    void print()
    {
        for (int i = 0; i < current; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    T &operator[](int i)
    {
        return arr[i];
    }
};

string names[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"};

void printPath(int currentVertex, vector<int> &parents)
{
    // cout << "called";
    // Base case : Source node has
    // been processed
    static int a = 0;
    if (currentVertex == -1)
    {
        return;
    }
    // cout << "CURRENT " << currentVertex << " " << parents[currentVertex] << " ";
    // for(int i=0;i<9;i++){cout<<parents[i]<<" ";}
    printPath(parents[currentVertex], parents);
    if (a++ > 0)
    {

        cout << "--->";
    }
    cout << names[currentVertex] << " ";
}

// A utility function to print
// the constructed distances
// array and shortest paths
void printSolution(int startVertex, vector<int> &distances,
                   vector<int> &parents, int d)
{
    // for(int i=0;i<9;i++){cout<<distances[i]<<" ";}

    cout << "Vertex\t Distance\tPath";

    for (int vertexIndex = 0; vertexIndex < v;
         vertexIndex++)
    {
        if (vertexIndex != startVertex and vertexIndex==d)
        {
            cout << "\n"
                 << startVertex << " -> ";
            cout << vertexIndex << " \t\t ";
            cout << distances[vertexIndex] << "\t\t";
            printPath(vertexIndex, parents);
        }
    }
}

vector<int> &dijkstra(int graph[][v], int s,int d)
{

    vector<int> dist(v, INT_MAX);
    dist[s] = 0;

    vector<int> parents(9);
    parents[s] = -1;
    vector<bool> fin(v, 0);

    for (int j = 0; j < v - 1; j++)
    {
        int u = -1, i;
        for (i = 0; i < v; i++)
        {
            if (!fin[i] && (u == -1 || dist[i] < dist[u]))
            {
                u = i;
            }
        }

        fin[u] = 1;

        for (int x = 0; x < v; x++)
        {
            if (graph[u][x] != 0 && fin[x] == 0)
            {
                dist[x] = min(dist[x], dist[u] + graph[u][x]);
                if (dist[x] == dist[u] + graph[u][x])
                    parents[x] = u;
            }
        }
    }
    // for(int i=0;i<9;i++){dist[i]=7;}
    // for(int i=0;i<9;i++){cout<<dist[i]<<" ";}

    // for (int i = 0; i < 9; i++)
    // {
    //     cout << parents[i] << " ";
    // }

    printSolution(s, dist, parents,d);
}

int main()
{

    int adj[v][v] = {{0, 4, 8, 0, 0, 0, 0, 0, 0},
                     {4, 0, 11, 8, 0, 0, 0, 0, 0},
                     {8, 11, 0, 0, 7, 1, 0, 0, 0},
                     {0, 8, 0, 0, 2, 0, 7, 4, 0},
                     {0, 0, 7, 2, 0, 6, 0, 0, 0},
                     {0, 0, 1, 0, 6, 0, 0, 2, 0},
                     {0, 0, 0, 7, 0, 0, 0, 14, 9},
                     {0, 0, 0, 4, 0, 2, 14, 0, 10},
                     {0, 0, 0, 0, 0, 0, 9, 10, 0}};

    int s, d;
    cin >> s;
cin>>d;
    vector<int> output = dijkstra(adj, s,d);

    // cout<<endl<<endl;
    // for (int i = 0; i < v; i++)
    // {
    //     cout << output[i] << " ";
    // }

    return 0;
}