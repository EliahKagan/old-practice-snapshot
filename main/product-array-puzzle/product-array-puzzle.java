import java.math.BigInteger;
import java.util.Scanner;

final class Solution {
    private static BigInteger[] readRecord(final Scanner sc)
    {
        final BigInteger[] a = new BigInteger[sc.nextInt()];
        for (int i = 0; i != a.length; ++i) a[i] = new BigInteger(sc.next());
        return a;
    }
    
    private static BigInteger product(final BigInteger[] a)
    {
        BigInteger p = BigInteger.ONE;
        for (final BigInteger n : a) p = p.multiply(n);
        return p;
    }
    
    private static void printGapProducts(final BigInteger[] a)
    {
        if (a.length == 0) return;
        
        final BigInteger p = product(a);
        
        String sep = "";
        for (final BigInteger n : a) {
            System.out.format("%s%s", sep, p.divide(n));
            sep = " ";
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                printGapProducts(readRecord(sc));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
