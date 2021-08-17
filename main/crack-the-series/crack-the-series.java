import java.math.BigInteger;
import java.util.List;
import java.util.Map;

final class BigPowers {
    private static final Map<Long, List<BigInteger>> powers
            = new java.util.HashMap<>();
    
    private static List<BigInteger> getPowerList(final long base)
    {
        List<BigInteger> a = powers.get(base);
        
        if (a == null) {
            a = new java.util.ArrayList<>();
            a.add(BigInteger.ONE);
            powers.put(base, a);
        }
        
        return a;
    }
    
    static BigInteger getPower(final long base, final int exponent)
    {
        final List<BigInteger> a = getPowerList(base);
        
        while (a.size() <= exponent)
            a.add(a.get(a.size() - 1).multiply(BigInteger.valueOf(base)));
        
        return a.get(exponent);
    }
    
    static BigInteger getPower(final long base, final BigInteger exponent)
    {
        return getPower(base, exponent.intValueExact());
    }
    
    private BigPowers() { } // the BigPowers class should not be instantiated
}

final class Solution {
    private static BigInteger getSequenceElement(final int n)
    {
        final long base = (n % 2 == 0 ? 3L : 2L);
        final int exponent = (n - 1) / 2;
        return BigPowers.getPower(2L, BigPowers.getPower(base, exponent));
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(getSequenceElement(sc.nextInt()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
