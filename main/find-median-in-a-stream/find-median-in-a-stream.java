import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

final class Solution {
    private static void add(final Queue<Integer> low,
                            final Queue<Integer> high, final int e)
    {
        (e < low.peek() ? low : high).add(e);
    }
    
    private static void rebalance(final Queue<Integer> low,
                                  final Queue<Integer> high)
    {
        if (Math.abs(low.size() - high.size()) == 2) {
            if (low.size() > high.size()) high.add(low.poll());
            else low.add(high.poll());
        }
    }
    
    private static int computeMedian(final Queue<Integer> low,
                                        final Queue<Integer> high)
    {
        return low.size() == high.size()
                ? (low.peek() + high.peek()) / 2
                : (low.size() > high.size() ? low.peek() : high.peek());
    }
    
    public static void main(final String[] args)
    {
        final int EXTRA = 8;
        
        try (final Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            final int h = n / 2 + EXTRA;
            
            final Queue<Integer> low = new PriorityQueue<>(h, (x, y) -> y - x);
            final Queue<Integer> high = new PriorityQueue<>(h);
            
            low.add(sc.nextInt());
            System.out.println(low.peek());
            
            while (--n != 0) {
                add(low, high, sc.nextInt());
                rebalance(low, high);
                System.out.println(computeMedian(low, high));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
