final class Solution {
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            final boolean prime = sc.nextBigInteger().isProbablePrime(1);
            System.out.println(prime ? "prime" : "not prime");
        }
    }
}
