#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define SIZE 100
#define white 0
#define gray 1
#define black 2
#define inf 10000

vector <int> adj[SIZE];
int color[SIZE], p[SIZE], d[SIZE], node, edge;

void graph()
{
    int u,v;
    cout << "No. of nodes: ";
    cin >> node;
    cout << endl;

    cout << "No. of edges: ";
    cin >> edge;
    cout << endl;

    cout << "Input edges: "<<endl;

    for(int i = 0; i < edge; i++)
    {
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "\nHere is the graph: " << endl;

    for(int i = 0; i<node; i++)
    {
        cout << i << ":";
        for(int j = 0; j < adj[i].size(); j++)
        {
            cout << "->" << adj[i][j];
        }

        cout << endl;
    }

}

void BFS(int source)
{

    cout << "Entered in BFS " << endl;
    for(int i = 0; i < node; i++)
    {
        color[i] = white;
        p[i] = -1;
        d[i] = inf;
    }

    color[source] = gray;
    p[source] = -1;
    d[source] = 0;

    queue<int> Q;

    Q.push(source);

    while(!Q.empty())
    {
        int u = Q.front();

        Q.pop();

        for(int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];

            if(color[v] == white)
            {
                color[v] = gray;
                p[v] = u;
                d[v] = d[u] + 1;

		Q.push(v);
            }
        }

	color[u] = black;
    }

    
}


void BFS_result()
{

    cout << "Node" << "   Color" << "  Distance" << "  Parent" << endl;
    for(int i = 0; i < node; i++)
    {
        cout << i << "        " << color[i] << "        " << d[i] << "         " << p[i] << endl;
    }

}


int main()
{
    graph();

    int source;

    cout << "Source node: ";
    cin >> source;

    BFS(source);
    BFS_result();

    return 0;
}
