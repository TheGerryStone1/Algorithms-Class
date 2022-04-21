//Fecha: 10 de abril de 2022.
//Materia: Analisis y diseño de algoritmos avanzados.
//Alumno: Gerardo Mora Beltran | A00827128

/*El problema consiste en determinar cuál es el valor de objetos más grande que se pueden
llevar una cantidad P de personas que pueden cargar un máximo de peso W. Los objetos tienen
2 variables relevantes para el problema, siendo estas el valor del objeto V y el peso del objeto P.
Este proceso de ingreso de datos se realizará N veces y se imprimirá el resultado acumulado del
valor de los objetos que se puede llevar una familia de M miembros.*/
//Complejidad final: O(2^n).

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

#define MAXOBJ 11
#define MAXPESO 101

struct object
{
    int value;
    int weight;
    float valWeight;
};

struct node
{
    int level; //Nivel en el que está el nodo.
    int accumVal;
    int accumWeight;
    int possValue;
    bool operator<(const node &other) const{
        return possValue < other.possValue;
    }
};

int calculateVP(vector<object> &data, int i, int auxVP, int auxWeight, int objectAmount, int bagWeight)
{
    int k = i + 1;
    while(k < objectAmount && auxWeight + data[k].weight <= bagWeight)
    {
        auxVP += data[k].value;
        auxWeight += data[k].weight;
        k++;
    }

    if(k < objectAmount) auxVP += ((bagWeight - auxWeight) * data[k].valWeight);

    return auxVP;
}

int branchAndBound(vector<object> &data, int objectAmount, int bagWeight)
{
    priority_queue<node> priorityQueue;
    int optimalValue = 0;
    int vp = calculateVP(data, -1, 0, 0, objectAmount, bagWeight);
    node start;
    start.level = -1;
    start.accumVal = 0; 
    start.accumWeight = 0;
    start.possValue = vp;

    priorityQueue.push(start);
    
    while(!priorityQueue.empty())
    {
        start = priorityQueue.top();
        priorityQueue.pop();
        
        if(start.accumVal > optimalValue) optimalValue = start.accumVal;
        if(start.possValue > optimalValue)
        {
            start.level++;
            start.possValue = calculateVP(data, start.level, start.accumVal, start.accumWeight, objectAmount, bagWeight);
            
            if(start.possValue > optimalValue && start.accumWeight <= bagWeight) priorityQueue.push(start);

            start.accumVal += data[start.level].value;
            start.accumWeight += data[start.level].weight;
            start.possValue = calculateVP(data, start.level, start.accumVal, start.accumWeight, objectAmount, bagWeight);

            if(start.possValue > optimalValue && start.accumWeight <= bagWeight) priorityQueue.push(start);

        }
    }

    return optimalValue;
}

int main()
{
    int v, w, objectAmount, bagWeight, cases, people, finalValue = 0;
    float vw;

    cin >> cases;

    vector<object> data;

    for(int c = 0; c < cases; c++)
    {
        cin >> objectAmount;

        for(int i = 0; i < objectAmount; i++)
        {
            cin >> v >> w;
            vw = v * 1.0 / w;
            object myData;
            myData.value = v;
            myData.weight = w;
            myData.valWeight = vw;
            data.push_back(myData);
        }

        cin >> people;
        
        for(int p = 0; p < people; p++)
        {
            cin >> bagWeight;
            finalValue += branchAndBound(data, objectAmount, bagWeight);
        }

        cout << "Max value is: " << finalValue << endl;

        data = {};
        finalValue = 0;
    }
}