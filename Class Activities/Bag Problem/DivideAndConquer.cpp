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

int divideAndConquer(vector<object> &data, int objectAmount, int bagWeight)
{
    if (objectAmount == 0 || data[objectAmount - 1].weight > bagWeight) return 0;
    else return max(divideAndConquer(data, objectAmount - 1, bagWeight), 
                                    data[objectAmount - 1].value + divideAndConquer(data, objectAmount - 1, bagWeight - data[objectAmount - 1].weight));
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

    cout << divideAndConquer(data, objectAmount, bagWeight) << endl;
}