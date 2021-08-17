import java.util.*;

final class Solution {
    public static void main(final String[] args)
    {
        final int[] factorials = { 1, 2, 6, 24, 120, 720, 5040, 40_320 };
        
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int i = Arrays.binarySearch(factorials, sc.nextInt());
                System.out.println(i < 0 ? 0 : 1);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
