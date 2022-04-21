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



void treeSearchHelper(vector<object> &data, int i, int accumValue, int accumWeight, int vp, int objectAmount, int bagWeight, int &optimalValue, vector<bool> &result, vector<bool> &inc)
{
    if(i < objectAmount && accumWeight <= bagWeight && vp > optimalValue)
    {
        if(accumValue > optimalValue)
        {
            optimalValue = accumValue;
            for(int j = 0; j < objectAmount; j++) result[j] = inc[j];
        }

        if(i + 1 < objectAmount)
        {
            //Include next object.
            inc[i + 1] = true;
            treeSearchHelper(data, i + 1, accumValue + data[i + 1].value, accumWeight + data[i  + 1].weight, vp, objectAmount, bagWeight, optimalValue, result, inc);
            
            //Not include next object.
            int auxVP = calculateVP(data, i + 1, accumValue, accumWeight, objectAmount, bagWeight);
            inc[i + 1] = false;
            treeSearchHelper(data, i, accumValue + data[i + 1].value, accumWeight + data[i  + 1].weight, auxVP, objectAmount, bagWeight, optimalValue, result, inc);
        }
    }
}

int treeSearch(vector<object> &data, int objectAmount, int bagWeight, vector<bool> &result)
{
    vector<bool> inc(objectAmount, false);
    int auxVP = calculateVP(data, -1, 0, 0, objectAmount, bagWeight);
    int optimalValue = 0;
    treeSearchHelper(data, -1, 0, 0, auxVP, objectAmount, bagWeight, optimalValue, result, inc);
    return optimalValue;
}

bool my_comp(const object &a, const object &b)
{
    return a.valWeight > b.valWeight;
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

    sort(data.begin(), data.end(), my_comp);

    cout << "Sorted data: " << '\n';
    for (int i = 0; i < objectAmount; i++) {
        cout << "Obj" << (i + 1) << " val: "<< data[i].value << " weight: " << data[i].weight << '\n';
    }

    vector<bool> result(objectAmount, false);
    cout << treeSearch(data, objectAmount, bagWeight, result) << endl;
    for (int i = 0; i<objectAmount; i++)
    {
        if (result[i]) cout << "Obj" << (i + 1) << '\n';
    }
}