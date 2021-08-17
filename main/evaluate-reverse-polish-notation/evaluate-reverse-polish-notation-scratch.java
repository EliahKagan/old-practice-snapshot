import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.function.IntBinaryOperator;

class Solution {
    private static final Map<String, IntBinaryOperator> OPERATORS =
            new HashMap<>();

    static {
        OPERATORS.put("+", (arg1, arg2) -> arg1 + arg2);
        OPERATORS.put("-", (arg1, arg2) -> arg1 - arg2);
        OPERATORS.put("*", (arg1, arg2) -> arg1 * arg2);
        OPERATORS.put("/", (arg1, arg2) -> arg1 / arg2);
    }

    public int evalRPN(final String... tokens) {
        final Deque<Integer> stack = new ArrayDeque<>();

        for (final String tok : tokens) {
            final IntBinaryOperator op = OPERATORS.get(tok.trim());

            if (op == null) stack.push(Integer.valueOf(tok));
            else {
                final int arg2 = stack.pop(), arg1 = stack.pop();
                stack.push(op.applyAsInt(arg1, arg2));
            }
        }

        if (stack.size() != 1) throw new IllegalArgumentException();
        return stack.pop();
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        final Solution s = new Solution();
        System.out.println(s.evalRPN("18"));
        System.out.println(s.evalRPN("2", "1", "+", "3", "*"));
        System.out.println(s.evalRPN("4", "13", "5", "/", "+"));
    }
}
