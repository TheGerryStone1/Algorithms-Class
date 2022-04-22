//Kruskal and Prim examples of MST.

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <climits>

using namespace std;

typedef pair<int, int> iPair;

struct Graph{
    //V is amount of vertex, E is amount of edges.
    int V, E, costMSTPrim, costMSTKruskal;

    vector<pair<int, pair<int, int>>> edges; //Kruskal.
    vector<vector<pair<int, int>>> adjacenceList;
    vector<pair<int,int>> selectedEdgesKruskal;

    vector<pair<int,int>> selectedEdgesPrim; //Prim.
    Graph(int V, int E){
        this->V = V;
        this->E = E;
        adjacenceList.resize(V);
        costMSTKruskal = costMSTPrim = 0;
    }

    void addEdge(int U, int V, int W)
    {
        edges.push_back({W, {U, V}}); //Costo, {Conexión de U -> V}.
        adjacenceList[U].push_back({V, W});
    }

    void Load();
    void Print();
    //void KruskalMST();
    void PrimMST();
    //void PrintEdgesKruskal();
    void PrintEdgesPrim();
};

void Graph::Load()
{
    int a, b, c;

    for(int i = 0; i < E; i++)
    {
        cin >> a >> b >> c;

        addEdge(a, b, c);
        addEdge(b, a, c);


    }
}

void Graph::Print()
{
    cout << "Adjacence list: " << endl;
    for(int i = 0; i < V; i++)
    {
        cout << " " << i << ": ";
        for(int j = 0; j < adjacenceList[i].size(); j++)
        {
            cout << "(" << adjacenceList[i][j].first << ", " << adjacenceList[i][j].second << ") ";
        }

        cout << endl;
    }
}

void Graph::PrintEdgesPrim()
{
    cout << "Selected Edges Prim: " << endl;
    for(auto it:selectedEdgesPrim)
    {
        cout << "(" << it.first << ", " << it.second << ") ";
    }
    
    cout << endl;
}

void Graph::PrimMST()
{
    int selectedSource = 0;
    costMSTPrim = 0;
    unordered_set<int> selected;
    unordered_set<int> missing;
    selected.insert(0);

    for(int i = 1; i < V; i++) 
    {
        missing.insert(i);
    }

    int connected = V - 1, minCost, selectedVertex;

    while(connected)
    {
        minCost = INT_MAX;
        
        for(auto it1:selected) //For each vertex in selected.
        {
            for(auto it2:adjacenceList[it1])
            {
                //Check each vertex in missing with the lowest cost.
                if(missing.find(it2.first) != missing.end() && it2.second < minCost)
                {
                    minCost = it2.second;
                    selectedVertex = it2.first;
                    selectedSource = it1;
                }
            }
        }
        costMSTPrim += minCost;
        selected.insert(selectedVertex);
        missing.erase(selectedVertex);
        selectedEdgesPrim.push_back({selectedSource, selectedVertex});
        connected--;
    }
}

int main()
{
    int V, E;
    cin >> V >> E;
    Graph G(V, E);
    
    G.Load();
    G.Print();
    G.PrimMST();
    
    cout << "El costo total del MST por Prim es: " << G.costMSTPrim << endl;
    
    G.PrintEdgesPrim();

    return 0;
}