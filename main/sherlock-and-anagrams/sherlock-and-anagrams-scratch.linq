<Query Kind="Program" />

internal static class Solution {
    private static int CountAnagrammaticPairs(string s)
    {
        if (s.Length < 2) return 0;
        
        var pairs = 0;
        
        for (var len = 1; len != s.Length; ++len) {
            var count = 0;
            var seen = new HashSet<string>();
            
            var istop = s.Length - len + 1;
            for (var i = 0; i != istop; ++i) {
                var w = s.Substring(i, len).ToCharArray();
                Array.Sort(w);
                if (!seen.Add(new string(w))) ++count;
            }
            
            pairs += count * (count - 1);
        }
        
        return pairs;
    }
}