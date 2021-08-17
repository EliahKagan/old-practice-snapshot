public class Solution {
    public int GetMoneyAmount(int n) {
        var table = new int[n + 2, n + 1];

        for (var kstart = 2; kstart <= n; ++kstart) {
            var i = 1;
            for (var k = kstart; k <= n; ++i, ++k) {
                var min = int.MaxValue;

                for (var j = i; j <= k; ++j) {
                    var cur = j + Math.Max(table[i, j - 1], table[j + 1, k]);
                    if (min > cur) min = cur;
                }

                table[i, k] = min;
            }
        }

        return table[1, n];
    }
}
