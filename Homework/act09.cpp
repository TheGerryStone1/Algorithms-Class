//Fecha: 3 de abril de 2022.
//Materia: Analisis y diseño de algoritmos avanzados.
//Alumno: Gerardo Mora Beltran | A00827128

/*El problema consiste en determinar el cuarto más alejado de la guarida de Rocky,
buscando que Rocky camine el mayor camino posible entre los caminos más cortos que
hay desde su guarida hasta todos los cuartos de la casa.*/
//Complejidad final: O(n^2)

#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;
#define INF INT_MAX
#define Edge pair<int, int> //Nodo al que llego y su costo.
#define Graph vector<vector<Edge>> //Grafo representado en una lista de adyacencias.
#define Vertex pair<int, int> //Distancia(Costo), ID.

vector<int> dijkstra(Graph &G, char cSource)
{
    int source = cSource - 'A';

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

            if(distance[v] > distance[u] + w) //Sobreescribe el valor acumulado de distancia si encuentra mejora en otro camino.
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
    int nodes, edges, cases, w, tempLongest = INT_MIN;
    char source = 'A', u, v, finalRoom;

    cin >> cases;
    cin >> nodes >> edges;

    for(int a = 0; a < cases; a++)
    {
        //Construcción de las conexiones entre nodos del grafo.
        Graph G(nodes);
        
        for(int i = 0; i < edges; i++)
        {
            cin >> u >> v >> w;
            //Arco de u->v con un costo de w.
            Edge edge1(v - 'A', w);
            G[u - 'A'].push_back(edge1);
            //Arco de v->u con un costo de w.
            Edge edge2(u - 'A', w);
            G[v - 'A'].push_back(edge2);
        }
    
        vector<int> distances = dijkstra(G, source);
        
        cout << "Case " << a + 1 << ": ";
        
        for(int i = 0; i < nodes; i++)
        {
            if(i != 0)
            {
                if(distances[i] != INF && tempLongest < distances[i])
                {
                    tempLongest = distances[i];
                    finalRoom = char(i + 'A');
                }
            }
        }

        cout << finalRoom << endl;

        distances = {};
        tempLongest = INT_MIN;
        cin >> nodes >> edges;
    }
}