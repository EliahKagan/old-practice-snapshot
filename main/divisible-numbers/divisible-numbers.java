final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int a = sc.nextInt(), b = sc.nextInt();
                System.out.println((a / b + 1) * b);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
