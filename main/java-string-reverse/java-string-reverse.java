// In spite of the name of the exercise, the solution herein does not actually
// reverse the string given as input. Some algorithms to do so are are similar
// to the algorithm used here to compare characters within the string.

final class Solution {
    public static void main(String[] args)
    {
        // The problem desription doesn't constrain the input string to being
        // non-empty, but the code prewritten in the buffer calls next(),
        // strongly suggesting that is the exercise author's intent.
        final String s = (new java.util.Scanner(System.in)).next();
        System.out.println(isPalindrome(s) ? "Yes" : "No");
    }

    private static boolean isPalindrome(String s)
    {
        for (int i = 0, j = s.length() - 1; i < j; ++i, --j)
            if (s.charAt(i) != s.charAt(j)) return false;

        return true;
    }

    private Solution() { } // this class should not be instantiated
}
