#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
using namespace std;

typedef pair<int, int> iPair;

struct Graph {
  int V, E;
  vector<pair<int, iPair>> edges;

  // Constructor
  Graph(int V, int E) {
    this->V = V;
    this->E = E;
  }

  void addEdge(int u, int v, int w) { edges.push_back({w, {u, v}}); }

  int kruskalMST(vector<pair<int, int>> &MST);
};

struct DisjointSets {
  int *parent, *rnk;
  int n;

  // Constructor
  DisjointSets(int n) {
    this->n = n;
    parent = new int[n + 1];
    rnk = new int[n + 1];

    for (int i = 0; i <= n; i++) {
      rnk[i] = 0;
      parent[i] = i;
    }
  }

  int find(int u) {
    if (u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);

    if (rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rnk[x] == rnk[y])
      rnk[y]++;
  }
};

int Graph::kruskalMST(vector<pair<int, int>> &MST) {
  int mst_wt = 0;

  sort(edges.begin(), edges.end());

  DisjointSets ds(V);

  vector<pair<int, iPair>>::iterator it;
  for (it = edges.begin(); it != edges.end(); it++) {
    int u = it->second.first;
    int v = it->second.second;

    int set_u = ds.find(u);
    int set_v = ds.find(v);

    if (set_u != set_v) {
      MST.push_back({u, v});

      mst_wt += it->first;

      ds.merge(set_u, set_v);
    }
  }

  return mst_wt; // NOLINT
}

int main(int argc, char **argv) {
  ifstream f(argv[1]);

  int V, E;
  f >> V >> E;
  Graph g(V, E);

  int u, v, w;
  for (int i = 0; i < E; i++) {
    f >> u >> v >> w;
    g.addEdge(u, v, w);
  }

  vector<pair<int, int>> MST;

  int mst_wt = g.kruskalMST(MST);

  sort(MST.begin(),MST.end());

  cout << mst_wt << "\n";
  cout << MST.size() << "\n";

  for (const auto edge : MST) {
    cout << edge.first << " " << edge.second << "\n";
  }

  return 0;
}
