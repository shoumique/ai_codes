#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

#define SIZE 100

struct Priority_Queue
{
    int node, dis;
    bool flag;
} Q[SIZE];

struct node
{
    int n, weight;
};

vector<node> adj[SIZE];
int node, edge;
int parent[SIZE];
int dis[SIZE];

int pop()
{
    int min = 10000, index = -1;

    for(int i = 0; i<node; i++)
    {
        if(Q[i].dis < min && Q[i].flag == true)
        {
            min = Q[i].dis;

            index = i;
        }
    }

    Q[index].flag = false;

    return index;
}

bool isEmpty()
{
    //bool flag = true;

    for(int i = 0; i < node; i++)
    {
        if(Q[i].flag == true)   // our goal is to find if any node's flag is set to true
            return false;       // Bcz it will mean there is still a node in the queue
                                // if we find a node which flag is set to true
                                // we immediately terminate and return the value
    }

    return true;            // So if the queue is empty this function will return yes (true)
}

void init_Priority_Queue()
{

    for(int i = 0; i < node; i++)
    {
        Q[i].node = i;
        Q[i].dis = 9999;
        Q[i].flag = true;

        dis[i] = 9999;
        parent[i] = -1;
    }
}

void Dijkstra(int source)
{
    cout << "Dijkstra Starts" << endl;
    init_Priority_Queue();

    dis[source] = 0;
    Q[source].dis = 0;

    while(isEmpty() != 1)
    {
        // cout << isEmpty() << endl;
        int u = pop();
        u = Q[u].node;

        cout << "First pop: " << u << endl;

        //cout << "Neighbour Size: " << adj[u].size() << endl;

        for(int i = 0; i < adj[u].size(); i++)
        {
            struct node temp;

            temp = adj[u][i];
            int v = temp.n;
            int weight = temp.weight;

            if(dis[v] > (dis[u] + weight))
            {
                dis[v] = dis[u] + weight;
                //cout << v << " ";

                parent[v] = u;
                Q[v].dis = dis[v];           // Updating the priority queue
                //cout << Q[v].dis << endl;
            }

        }

    }
}

void printPathUtil(int source, int j)
{
    if (parent[j] == -1)
        return;

    printPathUtil(source, parent[j]);

    cout << "->" << j;
}

void printPath(int source)
{
    int des;

    cout << "source is NODE: " << source << endl;
    cout << "Input destination: ";
    cin >> des;

    cout << endl;
    cout << source;
    printPathUtil(source, des);

    cout << endl;
}


void Graph()
{
    int u, v, w, source;
    //struct node* temp;

    //cout << "Enter number of nodes and edges: ";
    //cin >> node >> edge;
    //cout << endl;

    ifstream infile;
    infile.open("dijkstra.txt");

    infile >> node >> edge;

    for(int i = 0; i < edge; i++)
    {
        struct node temp;

        infile >> u >> v >> w;
        //infile >> v;
        //infile >> w;

        temp.n = v;
        temp.weight = w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
        //adj[u].push_back(temp);

    }

    for(int i = 0; i < node; i++)
    {
        cout << i;
        for(int j = 0; j < adj[i].size(); j++)
        {
            struct node temp;

            temp = adj[i][j];

            cout << "->" << temp.n;
        }

        cout << endl;
    }

    infile.close();
}

int main()
{
    int source;

    Graph();

    cout << endl;
    cout << "Input source: ";
    cin >> source;

    Dijkstra(source);

    cout << endl;

    printPath(source);

    for(int i = 0; i < node; i++)
        cout << "Node cost from source: node[" << i << "] : " << dis[i] << endl;

    return 0;
}
