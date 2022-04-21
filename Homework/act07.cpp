//Fecha: 14 de marzo de 2022.
//Materia: Analisis y diseño de algoritmos avanzados.
//Alumno: Gerardo Mora Beltran | A00827128

/*El problema consiste en determinar el tamaño de la secuencia no necesariamente
seguida de caracteres más grande de 2 strings.*/
//Complejidad final: O(n^2)
#include <iostream>
#include <stdio.h>

using namespace std;

int arr[1001][1001];

/*Función que llena las celdas de la matriz de acuerdo a 3 reglas. Si estamos en i = 0 y j = 0, 
se llenan de 0's esas secciones. En el resto de la matriz se llena una posición i,j con el valor
máximo almacenado en i-1,j o i,j-1 si los caracteres de ambas palabras no corresponden, caso 
contrario se le suma 1 a lo almacenado en la posición i-1,j-1. El valor de retorno será el valor 
que esté almacenado en la posición size1,size2 que representan los tamaños de las palabras.*/

//Complejidad: O(n^2)
int longestCommonSubsequence(string word1, string word2, int size1, int size2)
{
    arr[0][0] = 0;
    for(int column = 1; column < size2 + 1; column++) arr[0][column] = 0;
    for(int row = 1; row < size1 + 1; row++) arr[row][0] = 0;

    for (int i = 1; i < size1 + 1; i++)
    {
        for (int j = 1; j < size2 + 1; j++)
        {
            if(word1[i - 1] == word2[j - 1]) 
            {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            }

            else arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
        }
    }

    return arr[size1][size2];
}

int main()
{
    int repetitions;
    cin >> repetitions;

    string word1, word2;

    for(int i = 0; i < repetitions; i++)
    {
        cin >> word1;
        cin >> word2;
        int size1 = word1.length(), size2 = word2.length();

        cout << "Case " << i + 1 << ": " << longestCommonSubsequence(word1, word2, size1, size2) << endl;
    }
}