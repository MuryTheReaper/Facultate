import java.util.ArrayList;
import java.util.List;

public class Graph {

    private int n;
    private List<Integer>[] adj;

    public Graph(int n) {
        this.n = n;
        adj = new List[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }
    }

    public void addEdge(int u, int v) {
        adj[u].add(v);
        adj[v].add(u);
    }

    public int getLongestPath() {

        boolean[] visited = new boolean[n];
        int[] dist = new int[n];

        int max = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, visited, dist);
                for (int j = 0; j < n; j++) {
                    visited[j] = false;
                    max = Math.max(max, dist[j]);
                    dist[j] = 0;
                }
            }
        }

        return max;
    }

    private void dfs(int u, boolean[] visited, int[] dist) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dist[v] = dist[u] + 1;
                dfs(v, visited, dist);
            }
        }
    }
}

