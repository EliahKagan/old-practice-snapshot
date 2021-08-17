import java.util.Scanner;

final class RecordPrinter implements AutoCloseable {
    private final String sep;
    private boolean first = true;
    
    public RecordPrinter(String sep)
    {
        this.sep = sep;
    }
    
    public void print(final int value)
    {
        if (first) {
            System.out.print(value);
            first = false;
        }
        else System.out.format("%s%d", sep, value);
    }
    
    @Override
    public void close()
    {
        System.out.println();
    }
}

final class Solution {
    private static int[][] get(final Scanner sc, final int n)
    {
        final int[][] a = new int[n][n];
        
        for (int i = 0; i != n; ++i)
            for (int j = 0; j != n; ++j) a[i][j] = sc.nextInt();
        
        return a;
    }
    
    private static void putRotated(final int[][] a, final int n)
    {
        try (final RecordPrinter rp = new RecordPrinter(" ")) {
            for (int i = n; i-- != 0; )
                for (int j = 0; j != n; ++j) rp.print(a[j][i]);
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int n = sc.nextInt();
                putRotated(get(sc, n), n);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
