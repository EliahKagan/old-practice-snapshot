<Query Kind="Program" />

public class Solution {
    private sealed class CharIndices {
        public const int NotFound = -1;
    
        internal CharIndices(string text) {
            _rows = new List<int>['z' - 'a' + 1];
            
            for (var i = 0; i != _rows.Length; ++i)
                _rows[i] = new List<int>();
                
            for (var j = 0; j != text.Length; ++j)
                this[text[j]].Add(j);
        }
        
        internal int IndexOf(char ch, int start) {
            var row = this[ch];
            var k = row.BinarySearch(start);
            
            if (k < 0) {
                k = ~k;
                if (k == row.Count) return NotFound;
            }
            
            return row[k];
        }
        
        private List<int> this[char ch] => _rows[ch - 'a'];
    
        private readonly List<int>[] _rows;
    }

    public bool IsSubsequence(string s, string t) {
        var ci = new CharIndices(t);
        var start = -1;
        
        foreach (var ch in s) {
            start = ci.IndexOf(ch, ++start);
            if (start == CharIndices.NotFound) return false;
        }
        
        return true;
    }
}

private static void Main() { 
    var s = new Solution();
    s.IsSubsequence("abc", "ahbgdc").Dump();
    s.IsSubsequence("axc", "ahbgdc").Dump();
}
