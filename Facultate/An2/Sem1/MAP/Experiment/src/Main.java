
//class that calculates the longest path in an undirected and unwieghted graph
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = 2;
        Graph graph = new Graph(n + 1);
        graph.addEdge(0, 1);
        graph.addEdge(0, 2);

        System.out.println(graph.getLongestPath());
    }

}



