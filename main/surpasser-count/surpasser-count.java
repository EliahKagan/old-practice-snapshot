import java.util.Scanner;

final class Solution {
    private static int[] getRecord(final Scanner sc)
    {
        return java.util.stream.IntStream.range(0, sc.nextInt())
                                         .map(i -> sc.nextInt())
                                         .toArray();
    }
    
    private static int countSurpassers(final int[] a, int i)
    {
        int count = 0;
        
        for (final int x = a[i]; ++i != a.length; )
            if (x < a[i]) ++count;
        
        return count;
    }
    
    private static void printSurpasserCounts(final int[] a)
    {
        if (a.length == 0) throw new IllegalArgumentException();
        final int stop = a.length - 1;
        
        for (int i = 0; i != stop; ++i)
            System.out.format("%d ", countSurpassers(a, i));
        
        System.out.println(0);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                printSurpasserCounts(getRecord(sc));
        }
    }
}
