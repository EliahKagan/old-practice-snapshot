final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final int[] a = new int[sc.nextInt()];
                for (int k = sc.nextInt(); k > 0; --k) ++a[sc.nextInt() - 1];
                
                int acc = a[0];
                System.out.print(acc);
                
                for (int i = 1; i != a.length; ++i)
                    System.out.format(" %d", acc += a[i]);
                
                System.out.println();
            }
        }
    }
}
