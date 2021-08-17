import java.lang.Math;

final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) {
                final double n = sc.nextDouble();
                System.out.println(Math.round(Math.floor(Math.cbrt(n))));
            }
        }
    }
    
    private Solution() { }
}
