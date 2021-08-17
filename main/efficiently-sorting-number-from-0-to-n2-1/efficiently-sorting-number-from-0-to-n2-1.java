import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.function.IntUnaryOperator;
import java.util.stream.IntStream;

final class Solution {
    // Produces an array (of length size) of values, scanned from sc.
    private static int[] readRecord(final Scanner sc, final int size)
    {
        return IntStream.range(0, size).map(i -> sc.nextInt()).toArray();
    }
    
    // Prints all the numbers in an array.
    private static void print(final int[] values)
    {
        final StringJoiner sj = new StringJoiner(" ");
        for (final int x : values) sj.add(String.valueOf(x));
        System.out.println(sj);
    }
    
    // Makes a list of nulls representing empty bins. [countingSort() helper.]
    private static List<List<Integer>> initializeEmptyBins(int keyRange)
    {
        if (keyRange < 0) throw new IllegalArgumentException();
        
        final List<List<Integer>> bins = new ArrayList<>(keyRange);
        while (keyRange-- != 0) bins.add(null);
        return bins;
    }
    
    // Get a bin, creating it if necessary. [countingSort() helper.]
    private static List<Integer> getBin(final List<List<Integer>> bins,
                                        final int key)
    {
        List<Integer> ret = bins.get(key);
        
        if (ret == null) {
            ret = new ArrayList<>();
            bins.set(key, ret);
        }
        
        return ret;
    }
    
    // Stably group items into bins by key. [countingSort() helper.]
    private static List<List<Integer>> group(final int[] values,
            final int keyRange, final IntUnaryOperator keySelector)
    {
        final List<List<Integer>> bins = initializeEmptyBins(keyRange);
        
        for (final int x : values)
            getBin(bins, keySelector.applyAsInt(x)).add(x);
        
        return bins;
    }
    
    // Do a counting sort, selecting keys known to be in a prescribed range.
    private static void countingSort(final int[] values, // mutates values
            final int keyRange, final IntUnaryOperator keySelector)
    {
        int i = 0;
        for (final List<Integer> bin : group(values, keyRange, keySelector)) {
            if (bin != null)
                for (final int x : bin) values[i++] = x;
        }
        
        assert i == values.length;
    }
    
    // Do a two-pass radix sort, using countingSort().
    // Assumes every element of values is strictly less than radix * radix.
    private static void radixSort(final int[] values, final int radix)
    {
        if (radix <= 0) throw new IllegalArgumentException();
        
        countingSort(values, radix, x -> x % radix);
        countingSort(values, radix, x -> x / radix);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int size = sc.nextInt();
                final int[] values = readRecord(sc, size);
                radixSort(values, size * size);
                print(values);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
