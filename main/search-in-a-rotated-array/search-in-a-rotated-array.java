import java.util.*;

final class Solution {
    // Reads an array that can be partitioned into two contiguous subarrays,
    // such that every element of one is less than or equal to every element of
    // the other. Scans from sc, populating a and returning the index of the
    // split (i.e., of the first element in the second subarray).
    private static int readSplitSorted(final int[] a, final Scanner sc)
    {
        a[0] = sc.nextInt();
        int i = 1;
        while (i < a.length && a[i - 1] < (a[i] = sc.nextInt())) ++i;
        
        final int split = i;
        while (++i < a.length) a[i] = sc.nextInt();
        return split;
    }
    
    // Returns the index of key in the array a, where a must consist of two
    // non-overlapping contiguous subarrays such that every element of one is
    // less than or equal to every element of the other, where split is the
    // index of the split (i.e., of the first element in the second subarray).
    // Returns -1 if the element is not present.
    private static int searchSplitSorted(final int[] a, final int split,
                                         final int key)
    {
        final int i = key < a[0] ? Arrays.binarySearch(a, split, a.length, key)
                                 : Arrays.binarySearch(a, 0, split, key);
        return Math.max(i, -1);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] a = new int[sc.nextInt()];
                final int split = readSplitSorted(a, sc);
                System.out.println(searchSplitSorted(a, split, sc.nextInt()));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
