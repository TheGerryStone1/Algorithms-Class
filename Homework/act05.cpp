//Fecha: 11 de marzo de 2022.
//Materia: Analisis y diseño de algoritmos avanzados.
//Alumno: Gerardo Mora Beltran | A00827128

/*El problema consiste en determinar si es posible generar un tren objetivo usando los vagones de 2 vías de tren
que se unen. Tan sólo podemos usar el primer vagón que existe en cada vía de tren como referencia para determinar
la posibilidad de generación del tren objetivo. Complejidad final: O(n^2)*/

#include <iostream>
#include <iostream>
#include <vector>

using namespace std;

bool arr[1001][1001];

vector<int> trainBuilder(int trainSize) //Builds each train using its size as a reference to read each wagon. Complexity: O(trainSize).
{
    vector<int> train;
    int wagon;
    
    for(int tempWagon = 0; tempWagon < trainSize; tempWagon++)
    {
        cin >> wagon;
        train.push_back(wagon);
    }

    return train;
}

string railroad(vector<int> &train1, vector<int> &train2, vector<int> targetTrain, int size1, int size2) //Builds matrix's boolean values. Complexity = O(n^2)
{
    for(int column = 1; column < size2 + 1; column++) //Initializes row 0 with value false.
    {
        if(arr[0][column - 1] == true && targetTrain[column - 1] == train2[column - 1]) arr[0][column] = true;
        else arr[0][column] = false;
    }

    for(int row = 1; row < size1 + 1; row++) //Initializes column 0 with value false.
    {
        if(arr[row - 1][0] == true && targetTrain[row - 1] == train1[row - 1]) arr[row][0] = true;
        else arr[row][0] = false;
    }

    
    for (int i = 1; i < size1 + 1; i++)
    {
        for (int j = 1; j < size2 + 1; j++) //Fills each cell from i = 1 and j = 1 with value true if either the current character of train1 or train2 matches the target's current character and the matrix's previous row or column, respectively.
        {
            arr[i][j] = (targetTrain[i + j - 1] == train1[i - 1] && arr[i - 1][j]) || (targetTrain[i + j - 1] == train2[j - 1] && arr[i][j - 1]);
        }
    }
    
    if (arr[size1][size2]) return "possible";
    return "not possible";
}

int main()
{
    int size1 = 1, size2 = 1;
    string train1, train2, targetTrain;
    cin >> size1 >> size2;
    
    while(size1 != 0 && size2 != 0) //Keeps reading inputs so long as the sizes of train1 and train2 are not equal to 0.
    {
        vector<int> train1; //Restarts values in each iteration.
        vector<int> train2;
        vector<int> targetTrain;
        char tempWagon;

        train1 = trainBuilder(size1);
        train2 = trainBuilder(size2);
        targetTrain = trainBuilder(size1 + size2);
        
        arr[0][0] = true;

        cout << railroad(train1, train2, targetTrain, size1, size2) << endl;

        cin >> size1 >> size2;
    }
}