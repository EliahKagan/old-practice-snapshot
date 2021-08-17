import java.util.Scanner;

final class Solution {
    private static int getLineAsInt(final Scanner sc)
    {
        return Integer.parseInt(sc.nextLine().trim());
    }
    
    private static int bitonicMax(final String line, int n)
    {
        try (final Scanner sc = new Scanner(line)) {
            int x = sc.nextInt();
            for (int y; n-- > 0 && x <= (y = sc.nextInt()); ) x = y;
            return x;
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = getLineAsInt(sc); t > 0; --t) {
                final int n = getLineAsInt(sc);
                System.out.println(bitonicMax(sc.nextLine(), n));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
