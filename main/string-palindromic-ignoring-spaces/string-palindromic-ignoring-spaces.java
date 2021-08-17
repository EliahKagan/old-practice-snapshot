import java.util.Scanner;

final class Solution {
    private static boolean isPalindrome(final String s)
    {
        for (int i = 0, j = s.length() - 1; i < j; ++i, --j)
            if (s.charAt(i) != s.charAt(j)) return false;
        
        return true;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t) {
                final String s = String.join("", sc.nextLine().split("\\s+"));
                System.out.println(isPalindrome(s) ? "YES" : "NO");
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
