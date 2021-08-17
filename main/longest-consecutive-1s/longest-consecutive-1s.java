final class Solution {
    private static int maxConsecutiveOnes(int n)
    {
        for (int max_count = 0, count = 0; ; n >>>= 1) {
            if ((n & 1) == 0) {
                if (max_count < count) max_count = count;
                count = 0;
            }
            else ++count;
            
            if (n == 0) return max_count;
        }
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(maxConsecutiveOnes(sc.nextInt()));
        }
    }
    
    private Solution() { }; // the Solution class should not be instantiated
}
