/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * public interface NestedInteger {
 *     // Constructor initializes an empty nested list.
 *     public NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     public NestedInteger(int value);
 *
 *     // @return true if this NestedInteger holds a single integer, rather than a nested list.
 *     public boolean isInteger();
 *
 *     // @return the single integer that this NestedInteger holds, if it holds a single integer
 *     // Return null if this NestedInteger holds a nested list
 *     public Integer getInteger();
 *
 *     // Set this NestedInteger to hold a single integer.
 *     public void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     public void add(NestedInteger ni);
 *
 *     // @return the nested list that this NestedInteger holds, if it holds a nested list
 *     // Return null if this NestedInteger holds a single integer
 *     public List<NestedInteger> getList();
 * }
 */

import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Solution {
    public NestedInteger deserialize(final String expression) {
        final Matcher matcher = TOKEN_PATTERN.matcher(expression);
        final NestedInteger ret = consumeExpression(matcher);
        if (ret == null) throw new IllegalArgumentException("unmatched ]");
        return ret;
    }

    private static NestedInteger consumeExpression(final Matcher matcher) {
        if (!matcher.find())
            throw new IllegalArgumentException("token expected");

        final String token = matcher.group();

        switch (token) {
        case "[":
            return consumeOpenedList(matcher);
        case "]":
            return null;
        default:
            return new NestedInteger(Integer.parseInt(token));
        }
    }

    private static NestedInteger consumeOpenedList(final Matcher matcher) {
        final NestedInteger list = new NestedInteger();

        for (NestedInteger elem; (elem = consumeExpression(matcher)) != null; )
            list.add(elem);

        return list;
    }

    private static final Pattern TOKEN_PATTERN =
            Pattern.compile("[\\[\\]]|[-+]?\\d+");
}
