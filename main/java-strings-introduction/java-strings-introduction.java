final class Solution {
    public static void main(String[] args)
    {
        // read two string inputs
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        final String a = sc.next(), b = sc.next();

        // output a report on a few of their characteristics
        System.out.println(a.length() + b.length());
        System.out.println(a.compareTo(b) > 0 ? "Yes" : "No");
        System.out.format("%c%s %c%s%n",
                          Character.toUpperCase(a.charAt(0)), a.substring(1),
                          Character.toUpperCase(b.charAt(0)), b.substring(1));
    }

    private Solution() { } // this class should not be instantiated
}
