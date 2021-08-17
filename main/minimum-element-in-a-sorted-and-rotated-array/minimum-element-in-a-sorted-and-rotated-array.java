import java.util.Scanner;

final class Solution {
    // Finds the minimum value of n ints scanned from sc. Assumes the values
    // are all distinct and, except for a split as if by rotation, sorted.
    private static int readMin(int n, final Scanner sc)
    {
        final int front = sc.nextInt();
        
        while (--n > 0) {
            final int elem = sc.nextInt();
            if (elem < front) {
                sc.nextLine(); // skip the rest of the line
                return elem;
            }
        }
        
        return front; // line of values wasn't rotated (i.e., was rotated by 0)
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(readMin(sc.nextInt(), sc));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
