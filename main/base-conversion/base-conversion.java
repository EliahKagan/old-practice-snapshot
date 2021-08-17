import java.util.Scanner;
import java.util.StringJoiner;

final class Solution {
    private static void doBaseConversion(final Scanner sc,
            final StringJoiner sj, final int from, final int to)
    {
        sj.add(Integer.toString(Integer.parseInt(sc.next(), from), to));
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final StringJoiner sj = new StringJoiner(" ");
                doBaseConversion(sc, sj, 10, 2);
                doBaseConversion(sc, sj, 2, 10);
                doBaseConversion(sc, sj, 10, 16);
                doBaseConversion(sc, sj, 16, 10);
                System.out.println(sj.toString().toUpperCase());
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
