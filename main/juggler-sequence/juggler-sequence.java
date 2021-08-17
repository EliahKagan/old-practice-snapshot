final class Solution {
    private static long juggle(final long n) // gets next in juggler sequence
    {
        return (long)Math.pow(n, (n % 2L == 0L ? 0.5 : 1.5));
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                for (long n = sc.nextLong(); n != 1L; n = juggle(n))
                    System.out.format("%d ", n);
                
                System.out.println("1");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
