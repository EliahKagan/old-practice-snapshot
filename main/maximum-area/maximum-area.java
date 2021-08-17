final class Solution {
    private static long sqrt(final long n)
    {
        long r = (long)Math.sqrt(n);
        while (r * r < n) ++r;
        while (r * r > n) --r;
        return r;
    }
    
    private static long hypotenuseOfMaxAreaTriangle(final long area)
    {
        return sqrt(area * 4L);
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(hypotenuseOfMaxAreaTriangle(sc.nextLong()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
