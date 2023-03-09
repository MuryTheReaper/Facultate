#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string.h>
using namespace std;

class Graph {
  int V;
  list<int> *adj;

public:
  // Constructor and destructor
  Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
  }
  ~Graph() { delete[] adj; }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void rmvEdge(int u, int v);

  void printEulerTour();
  void printEulerUtil(int s);

  int DFSCount(int v, bool visited[]);

  bool isValidNextEdge(int u, int v);
};

void Graph::printEulerTour() {
  int u = 0;
  for (int i = 0; i < V; i++)
    if (adj[i].size() & 1) {
      u = i;
      break;
    }

  printEulerUtil(u);
  cout << endl;
}

void Graph::printEulerUtil(int u) {
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;

    if (v != -1 && isValidNextEdge(u, v)) {
      cout << u << "-" << v << " ";
      rmvEdge(u, v);
      printEulerUtil(v);
    }
  }
}

bool Graph::isValidNextEdge(int u, int v) {
  // The edge u-v is valid in one of the following two
  // cases:

  // v este singurul nod in care putem ajunge de aici
  int count = 0;
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i)
    if (*i != -1)
      count++;
  if (count == 1)
    return true;

  // verificam daca muchia u-v este "pod"
  bool visited[V]; // NOLINT
  memset(visited, false, V);
  int count1 = DFSCount(u, visited);

  rmvEdge(u, v);
  memset(visited, false, V);
  int count2 = DFSCount(u, visited);

  addEdge(u, v);

  return (count1 > count2) ? false : true;
}

void Graph::rmvEdge(int u, int v) {
  list<int>::iterator iv = find(adj[u].begin(), adj[u].end(), v);
  *iv = -1;

  list<int>::iterator iu = find(adj[v].begin(), adj[v].end(), u);
  *iu = -1;
}

int Graph::DFSCount(int v, bool visited[]) {
  visited[v] = true;
  int count = 1;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (*i != -1 && !visited[*i])
      count += DFSCount(*i, visited);

  return count;
}



int main(int argc, char **argv) {
  ifstream f(argv[1]);

  int V, E;
  f >> V >> E;

  Graph g(V);

  int u, v;
  for (int i = 0; i < E; i++) {
    f >> u >> v;
    g.addEdge(u, v);
  }

  g.printEulerTour();
  cout<<"\n";
  return 0;
}
