#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

#define white 0
#define grey 1
#define black 2

#define inf 10000

vector<int> adj[100];
int node, edge, tim = 0;
int color[100], d[100], f[100];
int pre[100];

void DFS_Visit(int u)
{
    color[u] = grey;
    tim  = tim+1;
    d[u] = tim;

    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];

        if(color[v] == white)
        {

            cout << "value of v: " << v << endl;

            pre[v] = u;

            DFS_Visit(v);
        }
    }

    color[u] = black;
    tim = tim+1;
    f[u] = tim;
}

void DFS(int source)
{
    for(int i = 0; i < node; i++)
    {
        color[i] = white;
        pre[i] = -1;
        f[i] = inf;
        d[i] = inf;
    }

    for(int i = 0; i < node; i++)
    {
        if(color[i] == white)
        {
            DFS_Visit(i);
        }
    }
}

void DFS_Print()
{
    for(int i = 0; i < node; i++)
    {
        cout << "Node: " << i << " color: " << color[i] << " previous: " << pre[i] << "    discovering time: " << d[i] << " finishing time: " << f[i] << endl;
    }
}

int main()
{
    int u, v, source;

    ifstream infile;
    infile.open("graph.txt");

    //cout << "No. of nodes: " << endl;
    infile >> node;
    //cout << "No. of edges: " << endl;
    infile >> edge;

    //cout << "Insert edges: " << endl;

    for(int i = 0; i<edge; i++)
    {
        infile >> u >> v;

        adj[u].push_back(v);
        //adj[v].push_back(u);
    }

    cout << "Here is the graph: " << endl;

    for(int i = 0; i<node; i++)
    {
        cout << i;
        for(int j = 0; j < adj[i].size(); j++)
        {
            cout << "->" << adj[i][j];
        }

        cout << endl;
    }

    cout << "Input source: ";
    cin >> source;
    cout << endl;

    DFS(source);

    DFS_Print();

    infile.close();

    return 0;
}
