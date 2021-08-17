import java.util.Scanner;

final class Solution {
    private static String extract(final Scanner sc)
    {
        return sc.nextLine().replaceAll("(?:LIE)+", " ").trim();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t)
                System.out.println(extract(sc));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
