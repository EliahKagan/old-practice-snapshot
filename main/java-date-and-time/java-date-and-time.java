import java.util.*;

final class Solution {
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            final int month = sc.nextInt() - 1;
            final int day = sc.nextInt();
            final int year = sc.nextInt();
            
            final Calendar cal = Calendar.getInstance();
            cal.set(year, month, day);
            
            final String weekday = cal.getDisplayName(
                    Calendar.DAY_OF_WEEK, Calendar.LONG, Locale.getDefault());
            
            System.out.println(weekday.toUpperCase());
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
