import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

final class Solution {
    private static String
    getFirstNonRepeating(final Map<Character, Integer> freqs)
    {
        return freqs.entrySet().stream().filter(kv -> kv.getValue() == 1)
                                        .map(kv -> kv.getKey().toString())
                                        .findFirst()
                                        .orElse("-1");
    }
    
    private static void run(final Scanner sc) // O(n^2) brute force algorithm
    {
        int n = sc.nextInt();
        final Map<Character, Integer> freqs = new LinkedHashMap<>(n);
        
        for (String sep = ""; n > 0; --n, sep = " ") {
            final Character c = sc.next().charAt(0);
            freqs.put(c, freqs.getOrDefault(c, 0) + 1);
            System.out.format("%s%s", sep, getFirstNonRepeating(freqs));
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
