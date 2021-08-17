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
        String sep = "";
        for (final int x : a) {
            System.out.format("%s%d", sep, x);
            sep = " ";
        }

        System.out.println();
    }

    private Solution() { throw new AssertionError(); }
}

final class Algo {
    static void quicksort(final int[] a) {
        quicksortSubarray(a, 0, a.length);
    }

    private static void quicksortSubarray(final int[] a,
                                          final int low, final int high) {
        if (high - low > 1) {
            final int mid = partition(a, low, high);
            quicksortSubarray(a, low, mid);
            quicksortSubarray(a, mid + 1, high);
        }
    }

    private static int partition(final int[] a,
                                 final int low, final int high) {
        swap(a, low, low + (high - low) / 2);
        final int pivot = a[low];

        int left = low;
        for (int right = low + 1; right != high; ++right)
            if (a[right] < pivot) swap(a, ++left, right);

        swap(a, low, left);
        return left;
    }

    private static void swap(final int[] a, final int i, final int j) {
        final int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }

    private Algo() { throw new AssertionError(); }
}
