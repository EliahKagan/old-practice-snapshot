import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        final int[] a = readRecord();
        Algo.mergesort(a);
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
    static void mergesort(final int[] a) {
        final int[] aux = new int[a.length];

        for (int delta = 1; delta < a.length; delta *= 2) {
            for (int mid = delta; mid < a.length; mid += delta * 2) {
                merge(aux, a, mid - delta,
                              mid,
                              Math.min(mid + delta, a.length));
            }
        }
    }

    private static void merge(final int[] aux, final int[] a,
                              final int low, final int med, final int high) {
        int count = 0, left = low, right = med;

        // Merge elements from both arrays until at least one is empty.
        while (left != med && right != high)
            aux[count++] = (a[right] < a[left] ? a[right++] : a[left++]);

        // Copy extra elements from the left side, if any.
        while (left != med) aux[count++] = a[left++];

        // Check that we got all elements except any extra right-side elements.
        if (count != right - low) throw new AssertionError();

        // Copy the elements back.
        int a_pos = low, aux_pos = 0;
        while (aux_pos != count) a[a_pos++] = aux[aux_pos++];
    }

    private Algo() { throw new AssertionError(); }
}
