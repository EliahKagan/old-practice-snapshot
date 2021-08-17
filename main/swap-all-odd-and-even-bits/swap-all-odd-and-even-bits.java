final class Solution {
    private static final int RIGHT = 0b01010101010101010101010101010101;
    private static final int LEFT = ~RIGHT;
    
    private static int swap(final int n)
    {
        return (n & RIGHT) << 1 | (n & LEFT) >>> 1;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(swap(sc.nextInt()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
