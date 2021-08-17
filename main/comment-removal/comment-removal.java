final class Solution {
    private static final String PATTERN = "/\\*.*?\\*/|//.*?\\\\n";
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t)
                System.out.println(sc.nextLine().replaceAll(PATTERN, ""));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
