final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        try {
            System.out.println(sc.nextInt() / sc.nextInt());
        }
        catch (java.lang.ArithmeticException e) {
            System.out.println(e);
        }
        catch (java.util.InputMismatchException e) {
            System.out.println(e.getClass().getName());
        }
    }

    private Solution() { } // this class should not be instantiated
}
