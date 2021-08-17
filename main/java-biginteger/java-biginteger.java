import java.math.BigInteger;

final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        final BigInteger a = new BigInteger(sc.nextLine());
        final BigInteger b = new BigInteger(sc.nextLine());

        System.out.println(a.add(b));
        System.out.println(a.multiply(b));
    }

    private Solution() { } // this class should not be instantiated
}
