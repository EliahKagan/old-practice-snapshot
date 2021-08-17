import java.math.BigInteger;

final class Solution {
    public static void main(final String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        for (int t = sc.nextInt(); t > 0; --t)
            System.out.println(factorial(new BigInteger(sc.next())));
    }
    
    private static BigInteger factorial(BigInteger n)
    {
        BigInteger acc = BigInteger.ONE;
        
        for (; n.compareTo(BigInteger.ONE) > 0; n = n.subtract(BigInteger.ONE))
            acc = acc.multiply(n);
        
        return acc;
    }
    
    private Solution() { } // this class should not be instantiated
}
