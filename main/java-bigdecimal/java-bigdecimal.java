import java.math.BigDecimal;

final class DescendingNumericLiteral
        implements Comparable<DescendingNumericLiteral> {
    private final String str;
    private final BigDecimal num;
    
    public DescendingNumericLiteral(final String str)
    {
        this.str = str;
        this.num = new BigDecimal(str);
    }
    
    @Override public String toString() { return str; }
    
    @Override public int compareTo(final DescendingNumericLiteral other)
    {
        return other.num.compareTo(num);
    }
}

final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int n = Integer.parseInt(sc.nextLine());
            
            final DescendingNumericLiteral[] a
                    = new DescendingNumericLiteral[n];
            
            for (int i = 0; i != n; ++i)
                a[i] = new DescendingNumericLiteral(sc.nextLine());
            
            java.util.Arrays.sort(a);
            
            for (final DescendingNumericLiteral x : a)
                System.out.println(x);
            
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
