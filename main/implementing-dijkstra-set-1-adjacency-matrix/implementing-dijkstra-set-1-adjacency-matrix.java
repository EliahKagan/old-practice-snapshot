/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

final class Entry implements Comparable<Entry> {
    Entry(final int vertex, final int cost) {
        this.vertex = vertex;
        this.cost = cost;
    }

    @Override
    public int compareTo(final Entry other) {
        return Integer.compare(cost, other.cost);
    }

    final int vertex, cost;
}

/*Complete the given function*/
class GfG {
    private static final int NOT_REACHED = Integer.MAX_VALUE;

    private static void display(final int[] costs) {
        final StringJoiner sj = new StringJoiner(" ");
        for (final int cost : costs) sj.add(Integer.toString(cost));
        System.out.print(sj);
    }

    public static void dijkstra(int graph[][], int src, int V) {
        final int[] costs = new int[V];
        Arrays.fill(costs, NOT_REACHED);

        final Queue<Entry> heap = new PriorityQueue<Entry>();
        heap.add(new Entry(src, 0));

        while (!heap.isEmpty()) {
            final Entry ent = heap.remove();
            if (costs[ent.vertex] != NOT_REACHED) continue;

            costs[ent.vertex] = ent.cost;

            final int[] row = graph[ent.vertex];

            for (int dest = 0; dest != V; ++dest) {
                if (row[dest] != 0 && costs[dest] == NOT_REACHED)
                    heap.add(new Entry(dest, ent.cost + row[dest]));
            }
        }

        display(costs);
    }
}
