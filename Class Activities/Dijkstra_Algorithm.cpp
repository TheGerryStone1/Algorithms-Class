#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;
#define INF INT_MAX
#define Edge pair<int, int> //Nodo al que llego y su costo.
#define Graph vector<vector<Edge>> //Grafo representado en una lista de adyacencias.
#define Vertex pair<int, int> //Distancia(Costo), ID.

void printGraph(Graph &G)
{
    for(int i = 0; i < G.size(); i++)
    {
        for(int j = 0; j < G[i].size(); j++)
        {
            cout << "(" << G[i][j].first << ", " << G[i][j].second << ") ";
        }

        cout << endl;
    }
}

vector<int> dijkstra(Graph &G, int source)
{
    vector<int> distance(G.size(), INF);
    distance[source] = 0;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex>> queue;
    Vertex sourceVertex(0, source);

    queue.push(sourceVertex);

    while(!queue.empty())
    {
        int u = queue.top().second;
        queue.pop();

        for(int i = 0; i < G[u].size(); i++)
        {
            Edge e = G[u][i];
            int v = e.first; //Hacia donde llego.
            int w = e.second; //Costo del arco.

            if(distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                Vertex vtx(distance[v], v);
                queue.push(vtx);
            }
        }
    }
    return distance;
}

int main()
{
    int nodes, edges, source, u, v, w;
    cin >> nodes >> edges >> source;

    Graph G(nodes);

    for(int i = 0; i < edges; i++)
    {
        cin >> u >> v >> w;
        //Arco de u->v con un costo de w.
        Edge edge1(v - 1, w);
        G[u - 1].push_back(edge1);
        //Arco de v->u con un costo de w.
        Edge edge2(u - 1, w);
        G[v - 1].push_back(edge2);


    }

    printGraph(G);
    
    vector<int> distances = dijkstra(G, source - 1);
    
    cout << "Distancias: " << endl;
    
    for(int i = 0; i < nodes; i++)
    {
        if(i != source - 1) cout << source << "--->" << (i + 1) << ": ";
        if (distances[i] == INF) cout << "Infinite" << endl;
        else cout << distances[i] << endl;
    }
}