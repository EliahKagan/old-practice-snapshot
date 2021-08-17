import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Solution {
    private static final class CharIndices {
        static final int NOT_FOUND = -1;

        CharIndices(final String text) {
            _rows = new ArrayList<>(ALPHA_LEN);

            while (_rows.size() != ALPHA_LEN)
                _rows.add(new ArrayList<>());

            for (int j = 0; j != text.length(); ++j)
                _rows.get(text.charAt(j) - 'a').add(j);
        }

        int indexOf(final char ch, final int start) {
            final List<Integer> row = _rows.get(ch - 'a');
            int k = Collections.binarySearch(row, start);

            if (k < 0) {
                k = ~k;
                if (k == row.size()) return NOT_FOUND;
            }

            return row.get(k);
        }

        private static final int ALPHA_LEN = 'z' - 'a' + 1;

        private final List<List<Integer>> _rows;
    }

    public boolean isSubsequence(final String s, final String t) {
        final CharIndices ci = new CharIndices(t);
        int start = -1;

        for (int i = 0; i != s.length(); ++i) {
            start = ci.indexOf(s.charAt(i), ++start);
            if (start == CharIndices.NOT_FOUND) return false;
        }

        return true;
    }
}

final class UnitTest {
    public static void main(final String[] args) {
        test("abc", "ahbgdc");
        test("axc", "ahbgdc");
    }

    private static void test(final String s, final String t) {
        System.out.println(new Solution().isSubsequence(s, t));
    }

    private UnitTest() { throw new AssertionError(); }
}
