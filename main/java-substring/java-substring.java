final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final String s = sc.next();
            final int start = sc.nextInt(), end = sc.nextInt();
            System.out.println(s.substring(start, end));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
