import java.util.*;

final class Solution {
    private static Map<String, String> getMap(final Scanner sc)
    {
        final Map<String, String> m = new HashMap<>();
        
        for (int n = Integer.parseInt(sc.nextLine()); n > 0; --n) {
            final String k = sc.next();
            m.put(k, sc.next());
        }
        
        return m;
    }
    
    private static void queryMap(final Map<String, String> m, final Scanner sc)
    {
        while (sc.hasNext()) {
            final String k = sc.next(), v = m.get(k);
            
            if (v == null)  System.out.println("Not found");
            else            System.out.format("%s=%s%n", k, v);
        }
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            queryMap(getMap(sc), sc);
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
