import java.util.Arrays;
import java.util.stream.IntStream;

final class Arith {
    private static int[] sieve(final int n)
    {
        final int len = (n + 1) / 2;
        final java.util.BitSet bits = new java.util.BitSet(len);
        bits.set(0, len);
        
        final int istop = (int)Math.sqrt(n) / 2 + 1;
        for (int i = 1; i != istop; ++i) {
            if (bits.get(i)) {
                final int jstep = i * 2 + 1;
                for (int j = (i + 1) * i * 2; j < len; j += jstep)
                    bits.clear(j);
            }
        }
        
        return IntStream.concat(IntStream.of(2),
                bits.stream().skip(1L).map(i -> i * 2 + 1)).toArray();
    }
    
    private static boolean hasPairSum(final int[] values, final int sum)
    {
        for (int i = 0; i != values.length; ++i) {
            final int key = sum - values[i];
            if (key < values[i]) break;
            
            if (Arrays.binarySearch(values, i, values.length, key) >= 0)
                return true;
        }
        
        return false;
    }
    
    private static int[] getPairSumElements(final int[] values)
    {
        return IntStream.of(values).filter(sum -> hasPairSum(values, sum))
                                   .toArray();
    }
    
    static int[] getSuperPrimes(final int n)
    {
        return getPairSumElements(sieve(n));
    }
    
    private Arith() { } // the Arith class should not be instantiated
}
    
final class Solution {
    public static void main(final String[] args)
    {
        final int nmax = 10_000_000;
        final int[] a = Arith.getSuperPrimes(nmax);
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int i = Arrays.binarySearch(a, sc.nextInt());
                System.out.println((i < 0 ? ~i - 1 : i) + 1);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
