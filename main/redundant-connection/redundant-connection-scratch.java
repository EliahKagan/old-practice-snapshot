final class DisjointSets {
    DisjointSets(final int count) {
        _elems = new Element[count];
        for (int i = 0; i != count; ++i) _elems[i] = new Element(i);
    }

    int findSet(final int i) {
        if (_elems[i].parent != i)
            _elems[i].parent = findSet(_elems[i].parent);

        return _elems[i].parent;
    }

    boolean union(int i, int j) { // returns true iff they were separate
        i = findSet(i);
        j = findSet(j);
        if (i == j) return false;

        if (_elems[i].rank < _elems[j].rank) {
            _elems[i].parent = j;
        } else {
            if (_elems[i].rank == _elems[j].rank) ++_elems[i].rank;
            _elems[j].parent = i;
        }

        return true;
    }

    private Element[] _elems;

    private static final class Element {
        int parent;
        int rank = 0;

        Element(final int id) { parent = id; }
    }
}

class Solution {
    public int[] findRedundantConnection(int[][] edges) {
        // I only really have edges.length elements, but they use 1-based
        // indexing, so I create an extra (initial) element and don't use it.
        final DisjointSets sets = new DisjointSets(edges.length + 1);

        for (final int[] edge : edges)
            if (!sets.union(edge[0], edge[1])) return edge;

        throw new IllegalArgumentException("no redundant edge found");
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        final Solution s = new Solution();

        final int[][][] test_cases = { // edges for each test case
                { { 1, 2 }, { 1, 3 }, { 2, 3 } },
                { { 1, 2 }, { 2 ,3 }, { 3 , 4 }, { 1, 4 }, { 1, 5 } }
        };

        for (final int[][] edges : test_cases) {
            final int[] result = s.findRedundantConnection(edges);
            System.out.format("%s %s%n", result[0], result[1]);
        }
    }

     private UnitTest() { throw new AssertionError(); }
}
