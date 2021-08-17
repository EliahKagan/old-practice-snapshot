final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t)
                System.out.println(sc.next().replaceAll("(.)\\1+", "$1"));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
