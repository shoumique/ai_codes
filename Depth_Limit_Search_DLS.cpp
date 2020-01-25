/* Input source = 0, destination = 3, level = 3. If the output */
/* exists within the given level, DFS will set the global variable 'flag' as true and */
/* the output will show "there is a path" */

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
int source, des, lim;
int color[100], d[100], f[100];
int pre[100];
bool flag = false;

bool DFS_Visit(int u, int des, int lim)
{
    bool check_true;

    // we have reached our destination successfully, return true
    // so, DFS_Visit function will get a value of 1
    if(u == des)
    {
        return true;
    }

    // limit reached, return false
    // so, DFS_Visit function will get a value of 0
    if(lim <= 0)
    {
        return false;
    }

    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];

        pre[v] = u;

        //Using recursion to check if the destination exists within the given level
        //The global variable flag will set to true, otherwise it will remain false
        //While going deeper each time, we are decreasing the level by 1

        check_true = DFS_Visit(v, des, lim-1); // 0 or 1 will be returned here based on the base cases

        //cout << check_true << endl;

        if(check_true)
        {
            flag = true;
        }
    }

    color[u] = black;
    tim = tim+1;
    f[u] = tim;

    return flag;

}

void DFS(int source, int des, int lim)
{
    for(int i = 0; i < node; i++)
    {
        color[i] = white;
        pre[i] = -1;
        f[i] = inf;
        d[i] = inf;
    }

    bool check = DFS_Visit(source, des, lim);

    if(check == true)
    {
        cout << "There is a path" << endl;
    }

    else
        cout << "There is no path available in the given limit." << endl;
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
    int u, v;

    ifstream infile;
    infile.open("graph_dls.txt");

    //cout << "No. of nodes: " << endl;
    infile >> node;
    //cout << "No. of edges: " << endl;
    infile >> edge;

    //cout << "Insert edges: " << endl;

    for(int i = 0; i<edge; i++)
    {
        infile >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /*cout << "Here is the graph: " << endl;

    for(int i = 0; i<node; i++)
    {
        cout << i;
        for(int j = 0; j < adj[i].size(); j++)
        {
            cout << "->" << adj[i][j];
        }

        cout << endl;
    }*/

    cout << "Input source, destination, limit: ";
    cin >> source >> des >> lim;
    cout << endl;

    DFS(source, des, lim);

    // DFS_Print();

    infile.close();

    return 0;
}
