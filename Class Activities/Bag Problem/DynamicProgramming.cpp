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

int arr[MAXOBJ][MAXPESO];

int dynamicBag(vector<object> data, int objectAmount, int bagWeight)
{
    arr[0][0] = 0;
    for(int column = 1; column < objectAmount + 1; column++) arr[0][column] = 0;
    for(int row = 1; row < bagWeight + 1; row++) arr[row][0] = 0;

    for(int i = 1; i < objectAmount + 1; i++)
    {
        for(int j = 1; j < bagWeight + 1; j++)
        {
            if(data[i - 1].weight > j) arr[i][j] = arr[i - 1][j];
            else arr[i][j] = max(arr[i - 1][j], arr[i - 1][j - data[i - 1].weight] + data[i - 1].value);
        }
    }

    return arr[objectAmount][bagWeight];
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

    cout << dynamicBag(data, objectAmount, bagWeight);
}