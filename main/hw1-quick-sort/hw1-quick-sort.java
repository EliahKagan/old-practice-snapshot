import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        final int[] a = readRecord();
        Algo.quicksort(a);
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
    static void quicksort(final int[] a) {
        quicksort_subarray(a, 0, a.length);
    }

    private static void quicksort_subarray(final int[] a,
                                           final int low, final int high) {
        if (high - low > 1) {
            final int mid = partition(a, low, high);
            quicksort_subarray(a, low, mid);
            quicksort_subarray(a, mid + 1, high);
        }
    }

    private static int partition(final int[] a,
                                 final int low, final int high) {
        final int center = low + (high - low) / 2;
        swap(a, low, center);
        final int pivot = a[low];

        int left = low;
        for (int right = low + 1; right != high; ++right)
            if (a[right] < pivot) swap(a, ++left, right);

        swap(a, low, left);
        return left;
    }

    private static void swap(final int[] a, final int i, final int j) {
        final int elem = a[i];
        a[i] = a[j];
        a[j] = elem;
    }

    private Algo() { throw new AssertionError(); }
}
