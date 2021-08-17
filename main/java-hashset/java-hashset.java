import java.util.*;

final class Solution {
    public static void main(final String[] args)
    {
        Set<String> s = new HashSet<>();
        
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t) {
                s.add(sc.nextLine());
                System.out.println(s.size());
            }
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
