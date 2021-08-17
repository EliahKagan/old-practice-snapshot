import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

final class Solution {
    private static final Pattern SENTENCE = Pattern.compile("[^.?!]+");
    private static final Pattern WORD = Pattern.compile("[A-Za-z]+");
    
    private static int countMatches(final String text, final Pattern pattern)
    {
        int count = 0;
        
        for (final Matcher matcher = pattern.matcher(text); matcher.find(); )
            ++count;
        
        return count;
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t) {
                final String line = sc.nextLine();
                
                System.out.format("%d %d%n", countMatches(line, SENTENCE),
                                             countMatches(line, WORD));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
