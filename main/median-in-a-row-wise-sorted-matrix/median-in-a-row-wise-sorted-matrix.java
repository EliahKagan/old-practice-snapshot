// Even if Arrays.sort in Java were not designed to perform well for partially
// sorted data, the problem constraints stipulate data sets no larger than
// 100 * 100 == 10000, so just about any method is fine as far as performance
// is concerned. Furthermore, the problem does not restrict what algorithm
// should be used, or what upper-bound time complexity must be met. Therefore
// I use the the simple approach of putting all the data into a one-dimensional
// array and sorting the array. If this needs to be sped up in the future, I
// would first consider using a selection algorithm (e.g., quickselect) to
// find the median without first sorting the array. There are, however,
// approaches that (directly) use the partial sortedness of each row being
// sorted, which could be applied. See https://stackoverflow.com/q/41414421.

import java.util.Arrays;
import java.util.Scanner;

final class Solution {
    private static int[] readRecord(final Scanner sc, final int size)
    {
        final int[] a = new int[size];
        for (int i = 0; i != size; ++i) a[i] = sc.nextInt();
        return a;
    }
    
    private static int findMedian(final int[] a) // mutates a (by sorting it)
    {
        if (a.length % 2 == 0)
            throw new IllegalArgumentException("need odd number of elements");
        
        Arrays.sort(a);
        return a[a.length / 2];
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] a = readRecord(sc, sc.nextInt() * sc.nextInt());
                System.out.println(findMedian(a));
            }
        }
    }
    
    private Solution() { throw new AssertionError(); }
}
