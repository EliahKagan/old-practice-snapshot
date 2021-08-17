final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final String s = sc.next();
                System.out.println(s.contains(sc.next()) ? "found"
                                                         : "not found");
            }
        }
    }
}
