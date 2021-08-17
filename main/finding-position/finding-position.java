final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                int k = 1;
                while (k <= n) k *= 2;
                System.out.println(k / 2);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
