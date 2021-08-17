final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                int acc = 0;
                for (int n = sc.nextInt(); n > 0; --n) acc ^= sc.nextInt();
                System.out.println(acc);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
