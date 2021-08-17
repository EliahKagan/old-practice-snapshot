import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

final class Solution {
    private static final Pattern PATTERN = Pattern.compile("\\d+");
    
    private static int countNumbers(final String s)
    {
        int count = 0;
        for (final Matcher m = PATTERN.matcher(s); m.find(); ) ++count;
        return count;
    }
    
    public static void main(final String[] args) throws IOException
    {
        try (final InputStreamReader isr = new InputStreamReader(System.in);
                final BufferedReader br = new BufferedReader(isr)) {
            for (int t = Integer.parseInt(br.readLine()); t > 0; --t) {
                br.readLine();
                System.out.println(countNumbers(br.readLine()));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
