import java.util.HashMap;

final class Solution {
    public static void main(String[] args)
    {
        final java.util.Scanner sc = new java.util.Scanner(System.in);
        System.out.println(isAnagram(sc.next(), sc.next()) ? "Anagrams"
                                                           : "Not Anagrams");
    }

    private static boolean isAnagram(String a, String b)
    {
        final int n = a.length();
        return n == b.length() && freqMap(a.toLowerCase(), n)
                                    .equals(freqMap(b.toLowerCase(), n));
    }

    private static HashMap<Character, Integer> freqMap(String s, int n)
    {
        final HashMap<Character, Integer> m
                = new HashMap<Character, Integer>();

        for (int i = 0; i != n; ++i) {
            final Character c = s.charAt(i);
            m.put(c, m.getOrDefault(c, 0) + 1);
        }

        return m;
    }

    private Solution() { } // this class should not be instantiated
}
