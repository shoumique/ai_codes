/* Minimum Priority Queue Raw Code using C++*/
#include<iostream>
using namespace std;

struct Priority_Queue
{
    int node, dis;
    bool flag;
}Q[100];

int Pop()
{
    int m = 1000, index;

    for(int i = 0; i < 3; i++)
    {
        cout << Q[i].dis << " < " << m << endl;
        if(Q[i].dis < m && Q[i].flag == true)
        {
            m = Q[i].dis;
            index = i;
        }
    }

    Q[index].flag = false;

    return index;
}

bool isEmpty()
{
    bool flag = true;

    for(int i = 0; i < node; i++)
    {
        if(Q[i].flag == true)  // our goal is to find if any node's flag is set to true
            flag = false;     // Bcz it will mean there is still a node in the queue
                             // if we find a node which flag is set to true
                            // we immediately terminate and return the value
    }

    return flag;            // So if the queue is empty this function will return yes (true)
}

int main()
{
    int node, dis;

    cin >> node >> dis;

    Q[0].node = node;
    Q[0].dis = dis;
    Q[0].flag = true;

    cin >> node >> dis;

    Q[1].node = node;
    Q[1].dis = dis;
    Q[1].flag = true;

    cin >> node >> dis;

    Q[2].node = node;
    Q[2].dis = dis;
    Q[2].flag = true;

    int desired_node = Pop();

    cout << Q[desired_node].node << endl;

    return 0;
}
