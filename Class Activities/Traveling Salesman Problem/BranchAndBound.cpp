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

void startMatrix(int arr[MAX][MAX])
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

void BranchAndBoundTSP(int arr[MAX][MAX], int n)
{

}

int main()
{
    //n is amount of nodes, m is amount of arcs.
    int n, m;
    cin >> n >> m;

    int arr[MAX][MAX];
    startMatrix(arr);
    readArcs(arr, m);
    cout << BranchAndBoundTSP(arr, n) << endl;
}

