final class Solution {
    private static int[] getValues()
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final int[] a = new int[sc.nextInt()];
            for (int i = 0; i != a.length; ++i) a[i] = sc.nextInt();
            return a;
        }
    }
    
    private static int countNegativeSubarrays(int[] a)
    {
        int count = 0;
        
        for (int i = 0; i != a.length; ++i) {
            for (int acc = 0, j = i; j != a.length; ++j)
                if ((acc += a[j]) < 0 ) ++count;
        }
        
        return count;
    }
    
    public static void main(final String[] args)
    {
        System.out.format("%d%n", countNegativeSubarrays(getValues()));
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
