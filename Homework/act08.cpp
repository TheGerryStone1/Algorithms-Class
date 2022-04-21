//Fecha: 3 de abril de 2022.
//Materia: Analisis y diseño de algoritmos avanzados.
//Alumno: Gerardo Mora Beltran | A00827128

/*El problema consiste en determinar la intensidad de sonido mínima que debemos
soportar para ir de punto A a punto B.*/
//Complejidad final: O(n^3)

#include <iostream>
#include <climits>
#include <vector>

using namespace std;
#define MAX 100
vector<int> result;

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

/*Función que encuentra el valor mínimo de sonido, tomando como comparación el valor máximo
entre las conexiones que existen en cierto punto del camino.*/
void Floyd_Warshall(int arr[MAX][MAX], int p[MAX][MAX], int n)
{
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(arr[i][k] != INT_MAX && arr[k][j] != INT_MAX) arr[i][j] = min(arr[i][j], max(arr[i][k], arr[k][j]));
            }
        }
    }
}

void checkPath(int p[MAX][MAX], int origin, int destiny)
{
    if (p[origin][destiny] != -1)
    {
        checkPath(p, origin, p[origin][destiny]);
        checkPath(p, p[origin][destiny], destiny);
    }
}

void consults(int arr[MAX][MAX], int p[MAX][MAX], int q)
{
    int origin, destiny;
    for(int i = 0; i < q; i++)
    {
        cin >> origin >> destiny;

        result.push_back(arr[origin - 1][destiny - 1]);
        checkPath(p, origin - 1, destiny - 1);
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
        cout << "Case " << i + 1 << ":" << endl;
        for(int j = 0; j < result.size(); j++)
        {
            if(result[j] != INT_MAX) cout << result[j] << endl;
            else cout << "no path" << endl;
        }
        result = {};
    }
}