final class Solution {
    private static int sumDivisors(final int n)
    {
        if (n < 3) {
            switch (n) {
                case 1:     return 1;
                case 2:     return 3;
                default:    throw new IllegalArgumentException();
            }
        }
        
        int stop = (int)Math.sqrt(n), sum = n + 1;
        
        if (stop * stop == n) sum += stop;
        else ++stop;
        
        for (int i = 2; i != stop; ++i)
            if (n % i == 0) sum += i + n / i;
        
        return sum;
    }
    
    private static boolean isDeficient(final int n)
    {
        return sumDivisors(n) < n * 2;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(isDeficient(sc.nextInt()) ? 1 : 0);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
