final class Solution {
    private static int popcount(int n)
    {
        int count = 0;
        for (; n != 0; n >>>= 1) count += (n & 1);
        return count;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(popcount(sc.nextInt()));
        }
    }
}
