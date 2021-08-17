final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        try {
            System.out.println(sc.nextInt() / sc.nextInt());
        }
        catch (java.util.InputMismatchException e) {
            // When the input string is numeric but does not fit in an int,
            // the read-in string is printed after the exception name,
            // unless that case is handled specially. I suspect there is a more
            // elegant way to do it than this, though.
            System.out.println("java.util.InputMismatchException");
        }
        catch (java.lang.RuntimeException e) {
            System.out.println(e);
        }
    }

    private Solution() { } // this class should not be instantiated
}
