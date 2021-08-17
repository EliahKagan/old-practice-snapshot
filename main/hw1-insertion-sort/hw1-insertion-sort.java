import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        final int[] a = readRecord();
        Algo.insertionSort(a);
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
    static void insertionSort(final int[] a) {
        if (a.length < 2) return;

        for (int right = 1; right != a.length; ++right) {
            final int elem = a[right];

            int left = right;
            for (; left != 0 && elem < a[left - 1]; --left)
                a[left] = a[left - 1];

            a[left] = elem;
        }
    }

    private Algo() { throw new AssertionError(); }
}
