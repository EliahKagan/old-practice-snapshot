/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/
import java.util.function.IntPredicate;
import java.util.stream.IntStream;

/*Complete the function below*/
class GfG
{
    public boolean hasCycle(final int V, final LinkedList<Integer>[] alist,
                            final boolean[] visited, final boolean[] explored)
    {
        if (alist.length != V || visited.length != V || explored.length != V)
            throw new IllegalArgumentException("arrays must be of length V");

        final IntPredicate hasCycleFrom = new IntPredicate() {
            @Override
            public boolean test(final int v) {
                if (explored[v]) return false;
                if (visited[v]) return true;

                visited[v] = true;
                if (alist[v].stream().anyMatch(this::test)) return true;
                explored[v] = true;

                return false;
            }
        };

        return IntStream.range(0, V).anyMatch(hasCycleFrom);
    }
}
