final class Solution {
    private static boolean incrementAndComputeCarryBit(final char[] digits)
    {
        for (int i = digits.length; i-- != 0; ) {
            if (digits[i] == '0') {
                digits[i] = '1';
                return false;
            }
            else digits[i] = '0';
        }
        
        return true;
    }
    
    public static void main(final String[] args)
    {
        try (final java.util.Scanner sc = new java.util.Scanner(System.in)) {
            for (int n = sc.nextInt(); n > 0; --n) {
                sc.next(); // don't need length
                final char[] digits = sc.next().toCharArray();
                if (incrementAndComputeCarryBit(digits)) System.out.print("1");
                System.out.println(digits);
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
