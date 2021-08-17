import java.util.stream.LongStream;

final class Solution {
    private static boolean isModifiedKaprekar(final long n)
    {
        final String s = String.valueOf(n * n);
        final int wl = s.length() / 2;
        final long left = Long.parseLong(s.substring(0, wl));
        final long right = Long.parseLong(s.substring(wl));
        return left + right == n;
    }
    
    private static LongStream getModifiedKaprekars(final long p, final long q)
    {
        final LongStream a = (p <= 1 ? LongStream.of(1) : LongStream.empty());
        
        final LongStream b = LongStream.rangeClosed(Math.max(p, 9), q)
                                       .filter(Solution::isModifiedKaprekar);
        
        return LongStream.concat(a, b);
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final long p = sc.nextLong(), q = sc.nextLong();
            
            final java.util.StringJoiner sj = new java.util.StringJoiner(" ");
            
            getModifiedKaprekars(p, q).mapToObj(String::valueOf)
                                      .forEachOrdered(sj::add);
            
            final String s = sj.toString();
            System.out.println(s.length() == 0 ? "INVALID RANGE" : s);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
