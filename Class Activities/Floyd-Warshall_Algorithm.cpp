#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void readArcs(int arr[MAX][MAX], int p[MAX][MAX], int m)
{
    int origin, destiny, cost;
    
    for(int i = 0; i < MAX; i++)
    {
        arr[i][i] = p[i][i] = 0;

        for(int j = 0; j < MAX; j++)
        {
            arr[i][j] = arr[j][i] = INT_MAX; //Represents infinity.
            p[i][j] = p[j][i] = -1; //Respresents non-existance.
        }
    }

    for(int i = 0; i < m; i++)
    {
        cin >> origin >> destiny >> cost;
        arr[origin - 1][destiny - 1] = arr[destiny - 1][origin - 1] = cost;
    }
}

void Floyd_Warshall(int arr[MAX][MAX], int p[MAX][MAX], int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(arr[i][k] != INT_MAX && arr[k][j] != INT_MAX && arr[i][k] + arr[k][j] < arr[i][j])
                {
                    arr[i][j] = arr[i][k] + arr[k][j];
                    p[i][j] = k;
                }
            }
        }
    }
}

void checkPath(int p[MAX][MAX], int origin, int destiny)
{
    if (p[origin][destiny] != -1)
    {
        checkPath(p, origin, p[origin][destiny]);
        cout << (p[origin][destiny] + 1) << "->";
        checkPath(p, p[origin][destiny], destiny);
    }
}

void consults(int arr[MAX][MAX], int p[MAX][MAX], int q)
{
    int origin, destiny;
    for(int i = 0; i < q; i++)
    {
        cin >> origin >> destiny;

        if(arr[origin - 1][destiny - 1] == INT_MAX) cout << "No path" << endl;
        else cout << "Cost: " << arr[origin - 1][destiny - 1] << " Path: " << origin << "->";
        checkPath(p, origin - 1, destiny - 1);
        cout << destiny << endl;
    }
}

void printArr(int arr[MAX][MAX], int p[MAX][MAX], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << arr[i][j] << "\t";
        }

        cout << endl;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << p[i][j] << "\t";
        }
        
        cout << endl;
    }
}

int main()
{
    //p is intermediate node with largest name.
    int arr[MAX][MAX], p[MAX][MAX];
    //n is amount of nodes, m is amount of arcs, q is amount of consults, t is amount of cases.
    int n, m, q, t;
    cin >> t;

    for(int i = 0; i < t; i++)
    {
        cin >> n >> m >> q;
        readArcs(arr, p, m);
        Floyd_Warshall(arr, p, n);
        consults(arr, p, q);
        printArr(arr, p, n);
    }
}