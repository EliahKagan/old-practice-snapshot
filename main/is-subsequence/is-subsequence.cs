public class Solution {
    public bool IsSubsequence(string s, string t) {
        if (s.Length == 0) return true;

        var i = 0;
        foreach (var ch in t)
            if (s[i] == ch && ++i == s.Length) return true;

        return false;
    }
}
