final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                int max_sum = 0, sum = 0, prev = Integer.MAX_VALUE;
                
                for (int n = sc.nextInt(); n > 0; --n) {
                    final int cur = sc.nextInt();
                    
                    if (cur <= prev) {
                        if (max_sum < sum) max_sum = sum;
                        sum = 0;
                    }
                    
                    sum += prev = cur;
                }
                
                System.out.println(Math.max(max_sum, sum));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
