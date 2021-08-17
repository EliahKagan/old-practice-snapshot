import java.util.ArrayList;
import java.util.List;

final class Solution {
    private static List<Integer> iota(final int max)
    {
        final List<Integer> a = new ArrayList<>(max + 1);
        for (int i = 0; i <= max; ++i) a.add(i);
        return a;
    }
    
    private static String cut(final String text, final int pos, final int len)
    {
        return text.substring(0, pos) + text.substring(pos + len);
    }
    
    private static <E> void cut(final List<E> a, final int pos, final int len)
    {
        a.subList(pos, pos + len).clear();
    }
    
    private static List<Integer> generateNonRemovableIndices(
            String text, final String pattern)
    {
        final List<Integer> indices = iota(text.length());
        final int len = pattern.length();
        
        for (int i; (i = text.indexOf(pattern)) >= 0; text = cut(text, i, len))
            cut(indices, i, len);
        
        return indices;
    }
    
    private static int computeMaxDelta(final int min_delta_considered,
            final int initial_value, final List<Integer> a)
    {
        int max_delta = min_delta_considered;
        
        int prev = initial_value;
        for (final int cur : a) {
            max_delta = Math.max(max_delta, cur - prev);
            prev = cur;
        }
        
        return max_delta;
    }
    
    private static int computeMaxIotaGap(final List<Integer> a)
    {
        return computeMaxDelta(1, -1, a) - 1;
    }
    
    private static int findMaxContiguousRemovableLength(final String text,
                                                        final String pattern)
    {
        return computeMaxIotaGap(generateNonRemovableIndices(text, pattern));
    }
    
    public static void main(final String[] args)
    {
        final String pattern = "100";
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                System.out.println(
                        findMaxContiguousRemovableLength(sc.next(), pattern));
            }
        }
    }
}
