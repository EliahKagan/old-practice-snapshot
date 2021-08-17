final class Solution {
    private static long sum(final long to)
    {
        return (to - 1L) * to / 2L;
    }
    
    private static long sum(final long to, final long by)
    {
        return sum(to / by + (to % by == 0L ? 0L : 1L)) * by;
    }
    
    private static long sum(final long to, final long by1, final long by2)
    {
        return sum(to, by1) + sum(to, by2) - sum(to, by1 * by2);
    }
    
    public static void main(final String[] args)
    {
        final long a = 3L, b = 5L; // factors
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(sum(sc.nextLong(), a, b));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
