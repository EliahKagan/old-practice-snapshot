import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

final class Solution {
    private static List<int[]> quadsWithSum(final int[] a, final int k)
    {
        final List<int[]> ret = new ArrayList<>();

        if (a.length < 4) return ret;
        final int gstop = a.length - 3, hstop = a.length - 2;

        for (int g = 0; g != gstop; ) {
            final int gval = a[g], hij_target = k - gval;

            for (int h = g + 1; h != hstop; ) {
                final int hval = a[h], ij_target = hij_target - hval;

                for (int i = h + 1, j = a.length - 1; i < j; ) {
                    final int ival = a[i], jval = a[j], ij_sum = ival + jval;

                    if (ij_sum == ij_target)
                        ret.add(new int[] { gval, hval, ival, jval });

                    if (ij_sum <= ij_target)
                        while (a[i] == ival && i < j) ++i;

                    if (ij_sum >= ij_target)
                        while (a[j] == jval && i < j) --j;
                }

                while (a[h] == hval && h != hstop) ++h;
            }

            while (a[g] == gval && g != gstop) ++g;
        }

        return ret;
    }

    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt(), k = sc.nextInt();
                final int[] a = new int[n];
                for (int i = 0; i != n; ++i) a[i] = sc.nextInt();

                Arrays.sort(a);
                final List<int[]> quads = quadsWithSum(a, k);

                if (quads.isEmpty()) {
                    System.out.println("-1");
                } else {
                    for (final int[] quad : quads) {
                        System.out.format("%d %d %d %d $",
                                          quad[0], quad[1], quad[2], quad[3]);
                    }

                    System.out.println();
                }
            }
        }
    }

    private Solution() { throw new AssertionError(); }
}
