final class Solution {
    public static void main(final String[] args)
    {
        final int[] spiral
                = { 0, 1, 2, 3, 7, 11, 15, 14, 13, 12, 8, 4, 5, 6, 10, 9 };
        
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] elems = new int[spiral.length];
                for (int i = 0; i != elems.length; ++i)
                    elems[i] = sc.nextInt();
                
                String sep = "";
                for (final int i : spiral) {
                    System.out.format("%s%d", sep, elems[i]);
                    sep = " ";
                }
                
                System.out.println();
            }
        }
    }
    
    private Solution() { } // the Solution class should not be isntantiated
}
