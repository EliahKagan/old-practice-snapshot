import java.text.*;

final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            DateFormat infmt = new SimpleDateFormat("hh:mm:ssaa");
            DateFormat outfmt = new SimpleDateFormat("HH:mm:ss");
            System.out.println(outfmt.format(infmt.parse(sc.nextLine())));
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
