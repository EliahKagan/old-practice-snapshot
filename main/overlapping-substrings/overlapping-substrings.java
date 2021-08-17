import java.util.regex.*;

final class Solution {
    private static void report(final Matcher m)
    {
        System.out.println(m.matches() ? "YES" : "NO");
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            int t = Integer.parseInt(sc.nextLine());
            if (--t < 0) return;
            
            final Matcher m = Pattern.compile(".*(?:XY.*YX|YX.*XY).*")
                                     .matcher(sc.nextLine());
            
            report(m);
            while (t-- > 0) report(m.reset(sc.nextLine()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
