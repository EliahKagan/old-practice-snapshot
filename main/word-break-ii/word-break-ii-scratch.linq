<Query Kind="Program" />

public class Solution {
    private const char END_MARK = '\0';

    private class Trie : Dictionary<char, Trie> { }
    
    private static Trie BuildTrie(IEnumerable<string> words) {
        var trie = new Trie();
        
        foreach (var word in words) {
            var cur = trie;
            
            foreach (var ch in word) {
                if (!cur.TryGetValue(ch, out var next)) {
                    next = new Trie();
                    cur.Add(ch, next);
                }
                
                cur = next;
            }
            
            cur[END_MARK] = null;
        }
        
        return trie;
    }
    
    private static List<int> GetOrMakeRow(List<int>[] adj, int i) {
        var row = adj[i];
        
        if (row == null) {
            row = new List<int>();
            adj[i] = row;
        }
        
        return row;
    }
    
    private static List<int>[] ConstructGraph(string text, Trie trie) {
        var adj = new List<int>[text.Length + 1];
        adj[text.Length] = new List<int>(); // mark the end as reachable
        
        for (var i = text.Length - 1; i != -1; --i) {
            var node = trie;
        
            for (var j = i; j != text.Length; ++j) {
                if (!node.TryGetValue(text[j], out node)) break;
                
                if (adj[j + 1] != null && node.ContainsKey(END_MARK))
                    GetOrMakeRow(adj, i).Add(j + 1);
            }
        }
        
        return adj;
    }
    
    private static IEnumerable<string> PathAsTokens(string text,
                                                    List<int> path)
        => from k in Enumerable.Range(0, path.Count - 1)
           select text.Substring(path[k], path[k + 1] - path[k]);
    
    private static List<string> EnumeratePaths(string text, List<int>[] adj) {
        var allPaths = new List<string>();
        if (adj[0] == null) return allPaths;
        
        var end = adj.Length - 1;
        var path = new List<int>();
        
        void Dfs(int i) {
            path.Add(i);
            
            if (i == end)
                allPaths.Add(string.Join(" ", PathAsTokens(text, path)));
            else
                foreach (var j in adj[i]) Dfs(j);
            
            path.RemoveAt(path.Count - 1);
        }
        
        Dfs(0);
        return allPaths;
    }

    public IList<string> WordBreak(string text, IList<string> words)
        => EnumeratePaths(text, ConstructGraph(text, BuildTrie(words)));
}

internal static class UnitTest {
    private static void test(string text, string concatenatedWords) {
        text.Dump(nameof(text));
        
        var words = concatenatedWords.Split();
        words.Dump(nameof(words));
        
        new Solution().WordBreak(text, words).Dump("WordBreak Results");
    }

    private static void Main() {
        test("catsanddog",
             "cat cats and sand dog");

        test("hcdarlrm",
             "lr m lrm hcdar wk");

        test("ilike",
             "i like sam sung samsung mobile ice cream icecream man go mango");

        test("idontlike",
             "i like sam sung samsung mobile ice cream icecream man go mango");

        test("woeismesaidthefarmerofowlbeetsandwelcomecheesefoobar",
             "said woe oo bar cheese f and welcome fowl the said armer farmer is owl me fo beets");

        test("woeismesaidthefarmerofowlbeetsandwelcomecheesefoobar",
             "said woe oo bar cheese f and welcome fowl the said armer farmer is owl me of beets");
    }
}
