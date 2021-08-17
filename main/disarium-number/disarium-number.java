final class Solution {
    private static boolean isDisarium(final String n)
    {
        int s = 0;
        
        for (int i = 0; i != n.length(); ++i) {
            final int d = n.charAt(i) - '0';
            int p = d;
            for (int j = i; j != 0; --j) p *= d;
            s += p;
        }
        
        return Integer.parseInt(n) == s;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(isDisarium(sc.next()) ? 1 : 0);
        }
    }
}
