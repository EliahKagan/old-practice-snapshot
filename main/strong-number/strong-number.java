final class Solution {
    private static final int[] factorials
            = { 1, 1, 2, 6, 24, 120, 720, 5040, 40_320, 362_880 };
    
    private static boolean isStrong(final String n)
    {
        int acc = 0;
        
        for (int i = 0; i != n.length(); ++i)
            acc += factorials[n.charAt(i) - '0'];
        
        return acc == Integer.parseInt(n);
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                System.out.println(isStrong(sc.next()) ? "Strong"
                                                       : "Not Strong");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
