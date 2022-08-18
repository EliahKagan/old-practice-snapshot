import java.util.*;

final class Solution {
    // holds start position in char stack; can be any char except ')', ']', '}'
    private static final char START_MARK = '\0';
    
    private static boolean isBalanced(final char[] str)
    {
        final Stack<Character> closers = new Stack<>();
        closers.push(START_MARK);
        
        for (final char c : str) {
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
            while (sc.hasNext())
                System.out.println(isBalanced(sc.nextLine().toCharArray()));
        }
    }
    
    private Solution() { } // the Solution class should not be instantiated
}