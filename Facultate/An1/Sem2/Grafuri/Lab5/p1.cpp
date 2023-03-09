#include <fstream>
#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define MAXV 100

bool bfs(int V, int rGraph[MAXV][MAXV], int s, int t, int parent[]) {

  bool visited[MAXV];
  memset(visited, 0, sizeof(visited));

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < V; v++) {
      if (visited[v] == false && rGraph[u][v] > 0) {
        if (v == t) {
          parent[v] = u;
          return true;
        }
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return false;
}

int fordFulkerson(int V, int graph[MAXV][MAXV], int s, int t) {
  int u, v;

  // graf pentru "residuri"
  int rGraph[MAXV][MAXV];

  for (u = 0; u < V; u++)
    for (v = 0; v < V; v++)
      rGraph[u][v] = graph[u][v];

  int parent[V]; // NOLINT

  int max_flow = 0;

  while (bfs(V, rGraph, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

int main(int argc, char **argv) {

  ifstream f(argv[1]);

  int V, E;
  f >> V >> E;

  int Graf[MAXV][MAXV];

  for (int i = 0; i < V; i++)
    for (int j = 0; j < V; j++)
      Graf[i][j] = 0;

  int u, v, w;
  for (int i = 0; i < E; i++) {
    f >> u >> v >> w;
    Graf[u][v] = w;
  }

  int s = 0, t = V - 1;

  cout << fordFulkerson(V, Graf, s, t)<<"\n";

  return 0;
}
