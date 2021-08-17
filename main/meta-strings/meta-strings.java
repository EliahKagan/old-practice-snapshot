import java.util.Scanner;

final class Solution {
    private static boolean areMeta(final String s, final String t)
    {
        if (s.length() != t.length()) return false;
        
        int i = -1, j = -1;
        for (int k = 0; k != s.length(); ++k) {
            if (s.charAt(k) != t.charAt(k)) {
                if  (i == -1) i = k;
                else if (j == -1) j = k;
                else return false;
            }
        }
        
        return j != -1 && s.charAt(i) == t.charAt(j)
                       && s.charAt(j) == t.charAt(i);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(areMeta(sc.next(), sc.next()) ? "1" : "0");
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
