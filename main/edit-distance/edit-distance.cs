public class Solution {
    public int MinDistance(string s, string t) {
        if (s.Length < t.Length) (s, t) = (t, s);

        var pre = new int[t.Length + 1];
        var cur = Enumerable.Range(0, pre.Length).ToArray();

        foreach (var i in Enumerable.Range(1, s.Length)) {
            (pre, cur) = (cur, pre);
            cur[0] = i;

            foreach (var j in Enumerable.Range(1, t.Length)) {
                if (s[i - 1] == t[j - 1])
                    cur[j] = pre[j - 1];
                else
                    cur[j] = 1 + Min3(cur[j - 1], pre[j], pre[j - 1]);
            }
        }

        return cur[t.Length];
    }

    private static int Min3(int x, int y, int z)
        => Math.Min(Math.Min(x, y), z);
}
