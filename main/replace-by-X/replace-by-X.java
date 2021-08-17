final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner((System.in))) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final String text = sc.next();
                final String pattern = String.format("(?:%s)+", sc.next());
                System.out.println(text.replaceAll(pattern, "X"));
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
