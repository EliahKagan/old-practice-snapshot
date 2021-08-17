import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        final int[] a = readRecord();
        Algo.heapsort(a);
        print(a);
    }

    private static int[] readRecord() {
        try (final Scanner sc = new Scanner(System.in)) {
            final int[] a = new int[sc.nextInt()];
            for (int i = 0; i != a.length; ++i) a[i] = sc.nextInt();
            return a;
        }
    }

    private static void print(final int[] a) {
        System.out.print("[");

        String sep = "";
        for (final int x : a) {
            System.out.format("%s%d", sep, x);
            sep = ",";
        }

        System.out.println("]");
    }

    private Solution() { throw new AssertionError(); }
}

final class Algo {
    static void heapsort(final int[] a) {
        int stop = a.length;
        if (stop < 2) return;

        // Convert the array into a binary maxheap.
        for (int parent = (stop - 1) / 2; parent != -1; --parent)
            sift_down(a, parent, stop);

        // Successively pop elements from the maxheap to sort the array.
        while (--stop != 0) {
            swap(a, 0, stop);
            sift_down(a, 0, stop);
        }
    }

    private static final int NO_CHILD = -1;

    private static void sift_down(final int[] a, int parent, final int stop) {
        for (; ; ) {
            final int child = pick_child(a, parent, stop);
            if (child == NO_CHILD || a[parent] >= a[child]) break;

            swap(a, parent, child);
            parent = child;
        }
    }

    private static int pick_child(final int[] a,
                                  final int parent, final int stop) {
        final int left = parent * 2 + 1;
        if (left >= stop) return NO_CHILD;

        final int right = left + 1;
        return right == stop || a[left] >= a[right] ? left : right;
    }

    private static void swap(final int[] a, final int i, final int j) {
        final int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    private Algo() { throw new AssertionError(); }
}
