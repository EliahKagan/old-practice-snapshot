final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt(), x = sc.nextInt();
                
                int i = 0;
                while (i != n && sc.nextInt() != x) ++i;
                
                if (i == n) {
                    System.out.println("OOPS! NOT FOUND");
                    continue;
                }
                
                System.out.println(i);
                while (++i != n) sc.nextInt(); // consume rest of array
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
