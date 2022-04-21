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
    int v, w, objectAmount, bagWeight;
    float vw;

    cin >> objectAmount >> bagWeight;

    vector<object> data;

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

    cout << branchAndBound(data, objectAmount, bagWeight);
}