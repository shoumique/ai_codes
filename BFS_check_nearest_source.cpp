/* This is a program to check the nearest Node from Two Source Nodes */
/* The program will check which Source Node is nearest from our given node */
/* Algorithm is to Run BFS with the source nodes then comparing the distance arrays */

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
int color2[SIZE], p2[SIZE], d2[SIZE]; // these are to store the previous BFS results

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

    //cout << "Entered in BFS " << endl;
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

    for(int i = 0; i < node; i++)
    {
        cout << i << "        " << color2[i] << "        " << d2[i] << "         " << p2[i] << endl;
    }

}

void check_nearest(int A, int B, int C)
{
    cout << A << ": " << d2[C] << endl;

    cout << B << ": " << d[C] << endl;

    if(d[C] > d2[C])
    {
        cout << "Source " << A << " is nearest" << endl;
    }

    else if(d[C] < d2[C])
    {
        cout << "Source " << B << " is nearest" << endl;
    }

    else
    {
        cout << "Both the distances are same." << endl;
    }
}

void Save_Prev()
{
    for(int i = 0; i < node; i++)
    {
        color2[i] = color[i];
        p2[i] = p[i];
        d2[i] = d[i];
    }

    for(int i = 0; i < node; i++)
    {
        color[i] = 0;
        p[i] = 0;
        d[i] = 0;
    }
}


int main()
{
    graph();

    int A, B, C;

    cout << "Source nodes: ";
    cin >> A >> B;

    cout << "Enter the Node you want to check: ";
    cin >> C;

    BFS(A);

    // Calling a function to save previous BFS results
    Save_Prev();

    BFS(B);

    //BFS_result();

    //Checking which Source is nearest from the given Node
    check_nearest(A, B, C);

    return 0;
}

