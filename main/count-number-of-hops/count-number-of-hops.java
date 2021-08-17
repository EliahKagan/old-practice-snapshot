final class Solution {
    // countSums(max_total)[h] is the number of sequences whose elements
    // are all 1, 2, or 3 and whose sum is h.
    private static long[] countSums(final int max_total)
    {
        long[] a = new long[max_total + 1];
        
        a[1] = 1L; // (1)
        a[2] = 2L; // (1, 1), (2)
        a[3] = 4L; // (1, 1, 1), (2, 1), (1, 2), (3)
        
        for (int h = 4; h <= max_total; ++h)
            a[h] = a[h - 3] + a[h - 2] + a[h - 1];
        
        return a;
    }
    
    public static void main(final String[] args)
    {
        final int max_height = 50;
        
        final long[] a = countSums(max_height);
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int i = sc.nextInt(); i > 0; --i)
                System.out.println(a[sc.nextInt()]);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
