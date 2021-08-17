import java.util.Scanner;

abstract class Heap {
    public Heap(final int capacity)
    {
        elems = new int[capacity];
    }
    
    public final int capacity() { return elems.length; }
    public final int size() { return last + 1; }
    
    public final int top() { return elems[0]; }
    
    public final int pop()
    {
        final int ret = elems[0];
        
        elems[0] = elems[last--];
        heapifyDown();
        
        return ret;
    }
    
    public final void push(final int x)
    {
        elems[++last] = x;
        heapifyUp();
    }
    
    protected abstract boolean comp(int x, int y); // e.g., < for min-heap
    
    private final int[] elems;
    private int last = -1; // index at the last element
    
    private void heapifyDown()
    {
        for (int i = 0; hasLeft(i); ) {
            // check which of the current element's children is the "least"
            final int j = (hasRight(i) && comp(rightVal(i), leftVal(i))
                            ? right(i)
                            : left(i));
            
            if (!comp(elems[j], elems[i])) break; // compare it with that one
            i = swap(i, j);
        }
    }
    
    private void heapifyUp()
    {
        for (int i = last; hasUp(i) && comp(elems[i], upVal(i)); )
            i = swap(i, up(i));
    }
    
    private int left(final int i) { return i * 2 + 1; }  // left child index
    private int right(final int i) { return i * 2 + 2; } // right child index
    private int up(final int i) { return (i - 1) / 2; }  // parent index
    
    private boolean hasLeft(final int i) { return left(i) <= last; }
    private boolean hasRight(final int i) { return right(i) <= last; }
    private boolean hasUp(final int i) { return i != 0; }
    
    private int leftVal(final int i) { return elems[left(i)]; }   // left child
    private int rightVal(final int i) { return elems[right(i)]; } // rt. child
    private int upVal(final int i) { return elems[up(i)]; }       // parent
    
    private int swap(int i, int j) // swaps ith and jth elements and returns j
    {
        final int tmp = elems[i];
        elems[i] = elems[j];
        elems[j] = tmp;
        
        return j;
    }
}

final class MinHeap extends Heap {
    public MinHeap(final int capacity) { super(capacity); }
    
    @Override
    protected boolean comp(final int x, final int y) { return x < y; }
}

final class MaxHeap extends Heap {
    public MaxHeap(final int capacity) { super(capacity); }
    
    @Override
    protected boolean comp(final int x, final int y) { return x > y; }
}

final class Solution {
    private static void add(final Heap low, final Heap high, final int e)
    {
        (e < low.top() ? low : high).push(e);
    }
    
    private static void rebalance(final Heap low, final Heap high)
    {
        if (Math.abs(low.size() - high.size()) == 2) {
            if (low.size() < high.size()) low.push(high.pop());
            else high.push(low.pop());
        }
    }
    
    private static double computeMedian(final Heap low, final Heap high)
    {
        if (low.size() == high.size()) return (low.top() + high.top()) / 2.0;
        return low.size() < high.size() ? high.top() : low.top();
    }
    
    private static void print(final double value)
    {
        System.out.format("%.1f%n", value);
    }
    
    public static void main(final String[] args)
    {
        final int EXTRA = 8;
        
        try (final Scanner sc = new Scanner(System.in)) {
            int n = sc.nextInt();
            final int h = n / 2 + EXTRA;
            final Heap low = new MaxHeap(h), high = new MinHeap(h);
            
            low.push(sc.nextInt());
            print(low.top());
            
            while (--n != 0) {
                add(low, high, sc.nextInt());
                rebalance(low, high);
                print(computeMedian(low, high));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
