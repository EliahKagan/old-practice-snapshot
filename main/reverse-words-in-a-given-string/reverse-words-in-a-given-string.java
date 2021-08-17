import java.util.regex.Pattern;

final class Solution {
    private static final Pattern DELIMITER = Pattern.compile("\\.");
    
    private static <T> void reverse(final T[] a)
    {
        for (int i = 0, j = a.length - 1; i < j; ++i, --j) {
            final T tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final String[] a = DELIMITER.split(sc.next());
                reverse(a);
                System.out.println(String.join(".", a));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
