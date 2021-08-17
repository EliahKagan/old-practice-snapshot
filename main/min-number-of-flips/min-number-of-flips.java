final class Solution {
    private static int minFlipsToAlternate(final String s)
    {
        int n = 0;
        
        for (int i = 0; i != s.length(); ++i)
            if ((s.charAt(i) ==  '0') == (i % 2 == 0)) ++n;
        
        return Math.min(n, s.length() - n);
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(minFlipsToAlternate(sc.next()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
