#include <iostream>
#include <queue>
#include <climits>

using namespace std;

#define MAX 21

struct Node{
    int level;
    int accumCost;
    int possibleCost;
    int previousVertex;
    int actualVertex;
    bool visited[MAX];
    bool operator<(const Node &other) const{
        return possibleCost >= other.possibleCost;
    }
};

void rootMatrix(int arr[MAX][MAX])
{
    for(int i = 0; i < MAX; i++)
    {
        arr[i][i] = 0;

        for(int j = i + 1; j < MAX; j++)
        {
            arr[i][j] = arr[j][i] = INT_MAX;
        }
    }
}

void readArcs(int arr[MAX][MAX], int m)
{
    int cost;
    char origin, destination;

    for(int i = 0; i < m; i++)
    {
        cin >> origin >> destination >> cost;
        arr[origin - 'A' + 1][destination - 'A' + 1] = arr[destination - 'A' + 1][origin - 'B' + 1] = cost;
    }
}

void calcPossCost(Node actualNode, int arr[MAX][MAX], int n)
{
    actualNode.possibleCost = actualNode.accumCost;
    int obtainedCost;

    for(int i = 0; i <= n; i++)
    {
        obtainedCost = INT_MAX;

        if(!actualNode.visited[i] || i == actualNode.actualVertex)
        {
            if(!actualNode.visited[i])
            {
                for(int j = 1; j <= n; j++)
                {
                    if (i != j && (!actualNode.visited[j] || j == 1)) obtainedCost = min(obtainedCost, arr[i][j]);
                }
            }

            else
            {
                for(int j = 1; j <= n; j++)
                {
                    if(!actualNode.visited[j]) obtainedCost = min(obtainedCost, arr[i][j]);
                }
            }
        }

        actualNode.possibleCost += obtainedCost;
    }
}

int BranchAndBoundTSP(int arr[MAX][MAX], int n)
{
    int optimalCost = INT_MAX;
    Node root;
    root.level = 0;
    root.accumCost = 0;
    root.possibleCost = 0;
    root.actualVertex = 1;
    root.previousVertex = 0;
    root.visited[1] = true;
    calcPossCost(root, arr, n);
    priority_queue<Node> priorityQueue;
    priorityQueue.push(root);

    while(!priorityQueue.empty())
    {
        root = priorityQueue.top();
        priorityQueue.pop();
        
        if(root.accumCost < optimalCost) optimalCost = root.accumCost;
        if(root.possibleCost < optimalCost)
        {
            root.level++;
            calcPossCost(root, arr, n);
            
            if(root.possibleCost < optimalCost) priorityQueue.push(root);

            root.accumCost += arr[root.level].accumCost;

            calcPossCost(root, arr, n);

            if(root.possibleCost > optimalCost) priorityQueue.push(root);

        }
    }

    return optimalCost;
}

int main()
{
    //n is amount of nodes, m is amount of arcs.
    int n, m;
    cin >> n >> m;

    int arr[MAX][MAX];
    rootMatrix(arr);
    readArcs(arr, m);
    cout << BranchAndBoundTSP(arr, n) << endl;
}

