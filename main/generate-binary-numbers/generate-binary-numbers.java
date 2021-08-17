final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                if (n < 1) throw new IllegalArgumentException();
                
                System.out.print(1);
                for (int i = 2; i <= n; ++i)
                    System.out.format(" %s", Integer.toBinaryString(i));
                
                System.out.println();
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
