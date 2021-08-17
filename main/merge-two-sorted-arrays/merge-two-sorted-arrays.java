import java.util.Scanner;
import java.util.stream.IntStream;

final class Solution {
    private static int[] getRecord(final Scanner sc, final int len)
    {
        return IntStream.range(0, len).map(i -> sc.nextInt()).toArray();
    }
    
    private static void putRemaining(final int[] arr, int i)
    {
        while (i != arr.length) System.out.format(" %d", arr[i++]);
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int alen = sc.nextInt(), blen = sc.nextInt();
                final int[] a = getRecord(sc, alen), b = getRecord(sc, blen);
                
                int i = 0, j = 0;
                System.out.print(a[i] > b[j] ? a[i++] : b[j++]);
                
                while (i != alen && j != blen)
                    System.out.format(" %d", (a[i] > b[j] ? a[i++] : b[j++]));
                
                putRemaining(a, i);
                putRemaining(b, j);
                System.out.println();
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instnatiated
}
