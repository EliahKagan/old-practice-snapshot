import java.util.Scanner;

final class Solution {
    private static final int ALPHA_LEN = 'z' - 'a' + 1;
    
    private static boolean isPangram(String s)
    {
        s = s.replaceAll("[^A-Za-z]+", "").toLowerCase();
        final boolean[] found = new boolean[ALPHA_LEN];
        for (int i = 0; i != s.length(); ++i) found[s.charAt(i) - 'a'] = true;
        
        for (final boolean b : found)
            if (!b) return false;
        
        return true;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t)
                System.out.println(isPangram(sc.nextLine()) ? 1 : 0);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
