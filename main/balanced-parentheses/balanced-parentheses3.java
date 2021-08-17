import java.util.*;

final class Solution {
    // holds start position in char stack; can be any char except ')', ']', '}'
    private static final char START_MARK = '\0';
    
    private static boolean isBalanced(final String str)
    {
        final Deque<Character> closers = new ArrayDeque<>(); // used as stack
        closers.push(START_MARK);
        
        for (int i = 0; i != str.length(); ++i) {
            final char c = str.charAt(i);
            
            switch (c) { // we will handle grouping characters (ignore others)
            case '(':
                closers.push(')');
                continue;
                
            case '[':
                closers.push(']');
                continue;
                
            case '{':
                closers.push('}');
                continue;
                
            case ')':
            case ']':
            case '}':
                if (closers.pop() != c) return false;
            }
        }
        
        return closers.pop() == START_MARK; // only balanced if all are closed
    }
    
    public static void main(final String[] args)
    {
        try (final Scanner sc = new Scanner(System.in)) {
            for (int t = Integer.parseInt(sc.nextLine()); t > 0; --t)
                System.out.println(isBalanced(sc.nextLine()) ? "YES" : "NO");
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}
