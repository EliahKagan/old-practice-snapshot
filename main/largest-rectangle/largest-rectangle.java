import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Scanner;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

final class Solution {
    private static LongStream zero()
    {
        return LongStream.of(0L);
    }
    
    private static LongStream zeroBracket(final LongStream values)
    {
        return LongStream.concat(LongStream.concat(zero(), values), zero());
    }
    
    private static long computeMaxArea(final LongStream heights)
    {
        final long[] h = zeroBracket(heights).toArray();
        final Deque<Integer> lefts = new ArrayDeque<>(h.length);
        long acc = 0L;
        
        for (int right = 0; right != h.length; ++right) {
            while (!lefts.isEmpty() && h[lefts.peek()] > h[right]) {
                final int left = lefts.pop();
                
                int width = right;
                if (!lefts.isEmpty()) width -= 1 + lefts.peek();
                
                acc = Math.max(acc, h[left] * width);
            }
            
            lefts.push(right);
        }
        
        return acc;
    }
    
    private static LongStream readRecord(final Scanner sc)
    {
        return IntStream.range(0, sc.nextInt()).mapToLong(i -> sc.nextLong());
    }
    
    public static void main(final String[] args) {
        try (final Scanner sc = new Scanner(System.in)) {
            System.out.println(computeMaxArea(readRecord(sc)));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
