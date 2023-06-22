// Rounak Das
// SE20UCSE149

#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

void addEdge(vector<vector<pair<int, int>>>& graph, int source, int destination, int cost) {
    graph[source].push_back(make_pair(destination, cost));
}

int find_min_distance(const vector<int>& distances, const vector<bool>& visited) {
    int minDistance = INF;
    int minIndex = -1;
    int numVertices = distances.size();

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void Djikstra(const vector<vector<pair<int, int>>>& graph, int source, vector<int>& distances, vector<int>& previous) {
    int numVertices = graph.size();
    vector<bool> visited(numVertices, false);
    distances.assign(numVertices, INF);
    previous.assign(numVertices, -1);
    distances[source] = 0;

    for (int i = 0; i < numVertices - 1; i++) {
        int u = find_min_distance(distances, visited);
        visited[u] = true;

        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }
}

// void printShortestPath(int vertex, const vector<int>& previous) {
//     if (vertex != -1) {
//         printShortestPath(previous[vertex], previous);
//         cout << "-> " << vertex << " ";
//     }
// }

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of nodes or routers in the network: ";
    cin >> numVertices;

    vector<vector<pair<int, int>>> graph(numVertices);

    cout << "Enter the source, destination, and cost of each edge:\n";


    for(int i = 0; i < numVertices; i++){
        for(int j = 0 ; j < numVertices; j++){
            int cost = 0;
            cin >> cost;
            addEdge(graph, i, j, cost); 
        }
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    vector<int> distances;
    vector<int> previous;
    
    Djikstra(graph, source, distances, previous);



    cout << "Shortest distances from vertex " << source << ":\n";


    for (int i = 0; i < numVertices; i++) {

        if (distances[i] != INF) {
            cout << "Vertex " << i << ": " << distances[i];
            // printShortestPath(i, previous);
            cout << " " << endl;
        } else {
            cout << "Vertex " << i << ": unreachable" << endl;
        }
    }

    return 0;
}