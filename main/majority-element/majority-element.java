import java.util.Scanner;

final class Solution {
    private static final int RANGE = 101;
    
    private static void run(final Scanner sc)
    {
        int[] freqs = new int[RANGE];
        final int n = sc.nextInt();
        for (int i = 0; i != n; ++i) ++freqs[sc.nextInt()];
        
        final int m = n / 2;
        for (int i = 0; i != n; ++i) {
            if (freqs[i] > m) {
                System.out.println(i);
                return;
            }
        }
        
        System.out.println("NO Majority Element");
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // // the Solution class should not be instantiated
}
