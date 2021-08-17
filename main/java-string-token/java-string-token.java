final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        final String[] tokens = sc.nextLine().split("[^A-Za-z]+");

        int i = (tokens.length != 0 && tokens[0].isEmpty()) ? 1 : 0;
        System.out.println(tokens.length - i);
        for (; i != tokens.length; ++i) System.out.println(tokens[i]);
    }

    private Solution() { } // this class should not be instantiated
}
