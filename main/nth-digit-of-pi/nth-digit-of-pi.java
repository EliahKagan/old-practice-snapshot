import java.math.BigDecimal;
import java.math.RoundingMode;

final class Solution {
    private static final int SCALE = 100_000;
    private static final RoundingMode MODE = RoundingMode.HALF_EVEN;
    
    private static BigDecimal atanOfReciprocal(final long n)
    {
        final BigDecimal arg = BigDecimal.valueOf(n);
        final BigDecimal square = BigDecimal.valueOf(n * n);
        
        BigDecimal acc = BigDecimal.ONE.divide(arg, SCALE, MODE), p = acc;
        
        for (long k = 3L, sgn = -1L; p.compareTo(BigDecimal.ZERO) != 0;
                                     k += 2L, sgn = -sgn) {
            p = p.divide(square, SCALE, MODE);
            final BigDecimal q = BigDecimal.valueOf(k * sgn);
            acc = acc.add(p.divide(q, SCALE, MODE));
        }
        
        return acc;
    }
    
    public static void main(final String[] args)
    {
        System.out.println(atanOfReciprocal(5));
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
