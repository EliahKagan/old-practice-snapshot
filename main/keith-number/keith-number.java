final class Solution {
    private static boolean isKeithNumber(final int n)
    {
        final String digits = String.valueOf(n);
        final int len = digits.length();
        final java.util.Queue<Integer> terms = new java.util.ArrayDeque<>(len);
        
        int acc = 0;
        
        for (int i = 0; i != len; ++i) {
            final int d = digits.charAt(i) - '0';
            if (d >= n) return d == n;
            acc += d;
            terms.add(d);
        }
        
        while (acc < n) {
            final int front = terms.remove();
            terms.add(acc);
            acc += acc - front;
        }
        
        return acc == n;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(isKeithNumber(sc.nextInt()) ? 1 : 0);
        }
    }
    
    private Solution() { } // the Solution class should not be instantated
}
