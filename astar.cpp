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
int heuristic[SIZE];
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
    for(int i = 0; i < node; i++)
    {
        if(Q[i].flag == true)
            return false;
    }

    return true;
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

void Astar(int source)
{
    cout << "Astar Starts: " << endl;
    init_Priority_Queue();

    dis[source] = 0;
    Q[source].dis = 0;

    while(!isEmpty())
    {
        int u = pop();
        u = Q[u].node;

        cout << u << " ";

        for(int i = 0; i < adj[u].size(); i++)
        {
            struct node temp;

            temp = adj[u][i];
            int v = temp.n;

            int weight = temp.weight;
            //int dist = dis[v];

            if(dis[v] > (dis[u] + weight))
            {

                //dis[v] = Q[v].dis;

                dis[v] = dis[u] + weight;
                Q[v].dis = dis[v] + heuristic[v];  // Update it with the heuristic cost
                parent[v] = u;
            }

        }

    }
}

void printPath(int source, int j)
{
    struct node temp;

    if (parent[j] == -1)
        return;

    printPath(source, parent[j]);

    cout << " -> " << j << " [cost: "<< dis[j] << "] ";
}

void Graph()
{
    int u, v, w, source;

    ifstream infile;
    infile.open("astar.txt");

    infile >> node >> edge;

    for(int i = 0; i < edge; i++)
    {
        struct node temp;

        infile >> u >> v >> w;

        temp.n = v;
        temp.weight = w;

        adj[u].push_back({v,w});
        //adj[v].push_back({u,w});

    }

    for(int i = 0; i < node; i++)
    {
        infile >> heuristic[i];
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
    int source, des;

    Graph();

    cout << "Input source: ";
    cin >> source;

    Astar(source);


    cout << endl;
    for(int i = 0; i < node; i++)
        cout << "Node cost from source: node[" << i << "] : " << dis[i] << endl;

    cout << "source is NODE: " << source << endl;
    cout << "Input destination: ";
    cin >> des;

    cout << endl;
    cout << source;
    printPath(source, des);

    cout << endl;

    return 0;
}
