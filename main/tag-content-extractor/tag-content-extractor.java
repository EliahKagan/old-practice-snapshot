import java.util.regex.*;

final class Solution {
    private static void parse(final Matcher m)
    {
        if (!m.find()) {
            System.out.println("None");
            return;
        }
        
        do System.out.println(m.group(2));
        while (m.find());
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            int n = Integer.parseInt(sc.nextLine());
            if (--n < 0) return;
            
            final Matcher m = Pattern.compile("<([^<>]+)>([^<>]+)</\\1>")
                                     .matcher(sc.nextLine());
            
            parse(m);
            while (n-- > 0) parse(m.reset(sc.nextLine()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
