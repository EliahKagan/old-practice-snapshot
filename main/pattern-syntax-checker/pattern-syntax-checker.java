final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        for (int n = Integer.parseInt(sc.nextLine()); n > 0; --n) {
            try {
                java.util.regex.Pattern.compile(sc.nextLine());
                System.out.println("Valid");
            }
            catch (java.util.regex.PatternSyntaxException e) {
                System.out.println("Invalid");
            }
        }
    }

    private Solution() { } // this class should not be instantiated
}
