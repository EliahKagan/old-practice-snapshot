import java.util.Arrays;
import java.util.Scanner;

final class MinMaxPair {
    MinMaxPair(final int min, final int max) {
        this.min = min;
        this.max = max;
    }

    final int min, max;
}

final class DisjointSets {
    DisjointSets(final int size) {
        _elems = new int[size];
        Arrays.fill(_elems, -1);
    }

    MinMaxPair computeComponentSizeRange(int startInclusive,
                                         final int endExclusive) {
        int lower = 0, upper = Integer.MIN_VALUE;

        for (; startInclusive < endExclusive; ++startInclusive) {
            // Comparing to -1 instead of 0 disregards unconnected nodes.
            if (_elems[startInclusive] < -1) {
                lower = Math.min(lower, _elems[startInclusive]);
                upper = Math.max(upper, _elems[startInclusive]);
            }
        }

        return new MinMaxPair(-upper, -lower);
    }

    void union(int i, int j) {   // union by size
        i = findSet(i);
        j = findSet(j);
        if (i == j) return;

        if (_elems[i] > _elems[j]) {    // _elems[j] is more negative
            _elems[j] += _elems[i];
            _elems[i] = j;
        } else {                        // _elems[i] is more negative
            _elems[i] += _elems[j];
            _elems[j] = i;
        }
    }

    private int findSet(int i) {    // find root, with full path compression
        int j = i;
        while (_elems[j] >= 0) j = _elems[j];

        while (i != j) { // path compression
            final int parent = _elems[i];
            _elems[i] = j;
            i = parent;
        }

        return j;
    }

    private final int[] _elems;
}

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            // determine how many disjoint sets we will start with
            int n = sc.nextInt();
            final int size = n * 2 + 1;

            // make the disjoint sets and perform unions as directed by input
            final DisjointSets sets = new DisjointSets(size);
            while (n-- > 0) sets.union(sc.nextInt(), sc.nextInt());

            // compute and report the minimum and maximum component sizes
            final MinMaxPair minmax = sets.computeComponentSizeRange(1, size);
            System.out.format("%d %d%n", minmax.min, minmax.max);
        }
    }

    private Solution() { throw new AssertionError(); }
}
