import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

final class HistoryNode {
    public HistoryNode next = null;
    public boolean repeated = false;
    public final char data;
    
    HistoryNode(final char data)
    {
        this.data = data;
    }
}

final class Solution {
    private static void run(final Scanner sc, int n)
    {
        final Map<Character, HistoryNode> lookup = new HashMap<>(n);
        HistoryNode left = new HistoryNode('\0'), right = left;
        
        for (String sep = ""; n-- > 0; sep = " ") {
            final char c = sc.next().charAt(0);
            final HistoryNode node = lookup.get(c);
            
            // insert a new node or mark an existing one non-unique
            if (node == null) {
                right = right.next = new HistoryNode(c);
                lookup.put(c, right);
            }
            else node.repeated = true;
            
            // find the earliest node that is still unique, if any
            while (left.next != null && left.next.repeated) left = left.next;
            
            if (left.next == null) System.out.format("%s-1", sep);
            else System.out.format("%s%c", sep, left.next.data);
        }
        
        System.out.println();
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = sc.nextInt(); t > 0; --t) run(sc, sc.nextInt());
        }
    }
    
    private Solution() { } // the Solution class shoult not be instantiated
}
