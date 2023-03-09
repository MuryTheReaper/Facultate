#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int flow, capacity;
  int u, v;

  Edge(int flow, int capacity, int u, int v) {
    this->flow = flow;
    this->capacity = capacity;
    this->u = u;
    this->v = v;
  }
};

struct Vertex {
  int h, e_flow; // inaltimea si excesul

  Vertex(int h, int e_flow) {
    this->h = h;
    this->e_flow = e_flow;
  }
};

class Graph {
  int V;
  vector<Vertex> ver;
  vector<Edge> edge;

  // impinge excesul
  bool push(int u);

  // repozitioneaza nod
  void relabel(int u);

  // initializare
  void preflow(int s);

  // functia pentru muchia inversa
  void updateReverseEdgeFlow(int i, int flow);

public:
  Graph(int V); // Constructor

  void addEdge(int u, int v, int w);

  int getMaxFlow(int s, int t);
};

Graph::Graph(int V) {
  this->V = V;

  // initializare
  for (int i = 0; i < V; i++)
    ver.push_back(Vertex(0, 0));
}

void Graph::addEdge(int u, int v, int capacity) {
  // initializare cu flow 0
  edge.push_back(Edge(0, capacity, u, v));
}

void Graph::preflow(int s) {
  // s are inaltime maxima
  ver[s].h = ver.size();

  for (int i = 0; i < edge.size(); i++) {
    // initializare flow din sursa
    if (edge[i].u == s) {
      edge[i].flow = edge[i].capacity;

      // initializam exces
      ver[edge[i].v].e_flow += edge[i].flow;

      // muchia inversa
      edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
    }
  }
}

// primul nod cu overflow
int overFlowVertex(vector<Vertex> &ver) {
  for (int i = 1; i < ver.size() - 1; i++)
    if (ver[i].e_flow > 0)
      return i;

  return -1;
}

// schimba flow pentru unde se face overflow
void Graph::updateReverseEdgeFlow(int i, int flow) {
  int u = edge[i].v, v = edge[i].u;

  for (int j = 0; j < edge.size(); j++) {
    if (edge[j].v == v && edge[j].u == u) {
      edge[j].flow -= flow;
      return;
    }
  }

  // adaugam muschia inversa
  Edge e = Edge(0, flow, u, v);
  edge.push_back(e);
}

// impinge overflow
bool Graph::push(int u) {
  // cautam unde sa impingem overflow
  for (int i = 0; i < edge.size(); i++) {
    // cautam sa fie adiacent cu u
    if (edge[i].u == u) {

      // nu putem impinge daca flow = capacity
      if (edge[i].flow == edge[i].capacity)
        continue;

      // trebuie sa impingem apa mai jos
      if (ver[u].h > ver[edge[i].v].h) {

        // impingem cat de mult putem
        int flow = min(edge[i].capacity - edge[i].flow, ver[u].e_flow);

        // ajustam overflow pentru cel de sus
        ver[u].e_flow -= flow;

        // crestem overflow pentru cel de jos
        ver[edge[i].v].e_flow += flow;

        edge[i].flow += flow;

        updateReverseEdgeFlow(i, flow);

        return true;
      }
    }
  }
  return false;
}

// schimbare inatlime
void Graph::relabel(int u) {

  int mh = INT_MAX;

  // cauta inaltimea minima
  for (int i = 0; i < edge.size(); i++) {
    if (edge[i].u == u) {

      if (edge[i].flow == edge[i].capacity)
        continue;

      if (ver[edge[i].v].h < mh) {
        mh = ver[edge[i].v].h;

        // schimba inaltimea
        ver[u].h = mh + 1;
      }
    }
  }
}

int Graph::getMaxFlow(int s, int t) {
  preflow(s);

  while (overFlowVertex(ver) != -1) {
    int u = overFlowVertex(ver);
    if (!push(u))
      relabel(u);
  }

  return ver.back().e_flow;
}

int main(int argc, char **argv) {

  ifstream f(argv[1]);

  int V, E;
  f >> V >> E;

  Graph g(V);

  int u, v, w;
  for (int i = 0; i < E; i++) {
    f >> u >> v >> w;
    g.addEdge(u, v, w);
  }

  int s = 0, t = V - 1;

  cout << g.getMaxFlow(s, t) << "\n";
  return 0;
}
