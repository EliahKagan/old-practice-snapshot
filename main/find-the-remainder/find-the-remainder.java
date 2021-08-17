import java.math.BigInteger;
import java.util.Scanner;

final class Solution {
    public static void main(final String[] args)
    {
        final BigInteger seven = BigInteger.valueOf(7);
        
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final BigInteger n = new BigInteger(sc.next());
                System.out.println(n.mod(seven));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
