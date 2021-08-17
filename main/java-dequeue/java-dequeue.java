import java.util.Map;
import java.util.Queue;
import java.util.Scanner;

final class Solution {
    private static final Integer ZERO = 0;
    
    // Adds one of key to bag, which may or may not already be an element.
    private static <T> void addOne(final Map<T, Integer> bag, final T key)
    {
        bag.put(key, bag.getOrDefault(key, ZERO) + 1);
    }
    
    // Removes one of the element key from bag, which is assumed to be present.
    private static <T> void removeOne(final Map<T, Integer> bag, final T key)
    {
        final int count = bag.get(key);
        
        if (count == 1) bag.remove(key);
        else bag.replace(key, count - 1);
    }
    
    // Reads an int from a scanner and add it to both a bag and a queue.
    private static void readOne(final Scanner sc,
            final Map<Integer, Integer> bag, final Queue<Integer> window)
    {
        final Integer elem = sc.nextInt();
        addOne(bag, elem);
        window.add(elem);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt(), m = sc.nextInt();
            
            final Map<Integer, Integer> bag = new java.util.HashMap<>();
            final Queue<Integer> window = new java.util.ArrayDeque<>(m);
            
            for (int i = m; i != 0; --i) readOne(sc, bag, window);
            
            int max_distinct = bag.size();
            for (n -= m; n != 0; --n) {
                removeOne(bag, window.remove()); // discard the oldest element
                readOne(sc, bag, window);
                
                max_distinct = Math.max(max_distinct, bag.size());
            }
            
            System.out.println(max_distinct);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
