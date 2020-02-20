#include<iostream>
#include<cmath>
using namespace std;

#define ROW 4
#define COL 4

int grid[ROW][COL] =
{
    {1, 1, 1, 1},
    {0, 0, 1, 1},
    {1, 1, 1, 1},
    {1, 1, 0, 1}
};

int solution[ROW][COL] =
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
};

struct Priority_Queue
{
    int x, y;
    double dis;
    bool flag;
} Q[4];                     ///Only need to store 4 elements at a time. Top, Right, Bottom and Left co-ordinate

int pop()
{
    double min = 10000;
    int index = -1;

    for(int i = 0; i<4; i++) /// as there are only 4 elements
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
    for(int i = 0; i < 4; i++)
    {
        if(Q[i].flag == true)   // our goal is to find if any node's flag is set to true
            return false;       // Bcz it will mean there is still a node in the queue
                                // if we find a node which flag is set to true
                                // we immediately terminate and return the value
    }

    return true;            // So if the queue is empty this function will return yes (true)
}

void init_priority_queue()
{
    for(int i = 0; i < 4; i++)
    {
        Q[i].x = -1;             // setting the co-ordinate as invalid or null
        Q[i].y = -1;
        Q[i].dis = 9999;
        Q[i].flag = true;
    }
}

double calc_dis(int start_x, int start_y, int des_x, int des_y)
{
    return ((double)sqrt ((des_x-start_x)*(des_x-start_x)+(des_y-start_y)*(des_y-start_y)));
}

bool isSafe(int x, int y)
{
    if(x >= 0 && x < ROW && y >= 0 && y < COL && grid[x][y] == 1)
        return true;

    return false;
}

bool greedySearch(int x, int y, int des_x, int des_y)
{
    init_priority_queue();       ///as for every current co-ordinate we are going to generate 4 new points, so,
                                ///we need to refresh or empty the priority queue every time, because we need to
                                ///delete previous 4 points that were stored in the queue currently.
                                ///after resetting the queue, we are going to store the new 4 points

    if(x == des_x && y == des_y) /// we have reached our goal co-ordinate
    {
        solution[x][y] = 1;
        return true;
    }

    //If we have not reached our goal co-ordinate yet, first check if we are in the right co-ordinate or not
    if(isSafe(x,y) == true)
    {
        solution[x][y] = 1;   //This co-ordinate is valid, so set the solution array as 1

        /// Now, we are going to check 4 points, TOP, DOWN, RIGHT, LEFT
        /// So, if the co-ordinates are valid we are going to calculate the heuristic or distance
        /// and store it in the priority queue.
        /// after storing the 4 neighbor, we are going to pick the least distant co-ordinate from the goal
        /// after that, we will set the current as this co-ordinate, that means we'll recursively call the function again

        if(isSafe(x+1, y) == true && solution[x+1][y] == 0) // Checking BOTTOM and also checking if the node is previously
        {                                                   // visited or not, if it is already visited then the 
                                                            // corresponding solution grid value must be set to 1. 
                                                            // So if it is already visited, we are not going to visit 
                                                            // it again, because that node might be the parent node 
                                                            // of current node, so if we allow this visit, the code will
                                                            //  fall into infinite loop. So we are only allowing unvisited
                                                            // node.
            Q[0].x = x+1;
            Q[0].y = y;
            Q[0].flag = true;

            Q[0].dis = calc_dis(x+1, y, des_x, des_y);
        }

        if(isSafe(x-1, y) == true && solution[x-1][y] == 0) // Checking TOP
        {
            Q[1].x = x-1;
            Q[1].y = y;
            Q[1].flag = true;

            Q[1].dis = calc_dis(x-1, y, des_x, des_y);
        }

        if(isSafe(x, y+1) == true && solution[x][y+1] == 0) //Checking RIGHT
        {
            Q[2].x = x;
            Q[2].y = y+1;
            Q[2].flag = true;

            Q[2].dis = calc_dis(x, y+1, des_x, des_y);
        }

        if(isSafe(x, y-1) == true && solution[x][y-1] == 0) // Checking LEFT
        {
            Q[3].x = x;
            Q[3].y = y-1;
            Q[3].flag = true;

            Q[3].dis = calc_dis(x, y-1, des_x, des_y);
        }

        int index = pop(); // Selecting the index of minimum distant node from the queue

        
         x = Q[index].x; // Setting the x,y as the minimum distant node
         y = Q[index].y;
       

        if(greedySearch(x, y, des_x, des_y) == true) // Recursively calling the function
            return true;                            // It means, if the right co-ordinate is the nearest from the
                                                    // goal, we are now at the right.

        solution[x][y] == 0;                        // If all the above options have failed, that means we have
        return false;                               // failed to reach the goal node with this path, so set all
                                                    // the path to 0 and return false
    }
    
    return false;
}

void printSolution()
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
            cout << " " << solution[i][j] << " ";

        cout << endl;
    }
}

void heuristic(int des_x, int des_y)
{
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++)
            cout << "  " << calc_dis(i,j,des_x,des_y) << "  ";
        cout << endl;
    }
}

int main()
{
    int x, y, des_x, des_y;

    cout << "Input source co-ordinate: ";
    cin >> x >> y;

    cout << "Input destination co-ordinate: ";
    cin >> des_x >> des_y;

    bool result = greedySearch(x, y, des_x, des_y);

    if(result == 0)
        cout << "\nTHERE IS NO PATH AVAILABLE TO THE DESTINATION" << endl;
    
    else {
        
        cout << "\nPATH AVAILABLE TO THE DESTINATION" << endl;
        printSolution();
        
    }

    cout << endl;
    heuristic(des_x, des_y);

    return 0;
}

//Reference:https://www.geeksforgeeks.org/rat-in-a-maze-backtracking-2/
