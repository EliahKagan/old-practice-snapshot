import java.math.BigInteger;
import java.util.Scanner;

final class Solution {
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            final BigInteger a = sc.nextBigInteger();
            final BigInteger b = sc.nextBigInteger();
            final int n = sc.nextInt();
            System.out.println(fibonacciModified(a, b, n));
        }
    }

    private static BigInteger
    fibonacciModified(BigInteger a, BigInteger b, final int n) {
        for (int i = 2; i < n; ++i) {
            final BigInteger c = b.pow(2).add(a);
            a = b;
            b = c;
        }

        return b;
    }

    private Solution() {
        throw new AssertionError();
    }
}
