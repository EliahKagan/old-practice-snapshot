final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                int n = sc.nextInt();
                long b = sc.nextLong();
                
                while (n-- > 0)
                    if (sc.nextLong() == b) b *= 2L;
                
                System.out.println(b);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
