import java.util.Scanner;

final class Solution {
    private static int josephus2(final int n)
    {
        // See: https://en.wikipedia.org/wiki/Josephus_problem#k.3D2
        return (n ^ Integer.highestOneBit(n)) << 1 | 1;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(josephus2(sc.nextInt()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
