<Query Kind="Program" />

public class Solution {
    private const int Start = 1, Stop = 10; // use values in [start, stop)

    public IList<IList<int>> CombinationSum3(int k, int n) {
        var ret = new List<IList<int>>();
        var way = new int[k];
        
        void Dfs(int len, int min, int sum) {
            if (sum <= 0) {
                if (sum == 0 && len == k) ret.Add((int[])way.Clone());
                return;
            }
            
            if (len != k && min != Stop) {
                way[len] = min;
                Dfs(len + 1, min + 1, sum - min);
                Dfs(len, min + 1, sum);
            }
        }
        
        Dfs(0, Start, n);
        return ret;
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum3(3, 7).Dump();
        s.CombinationSum3(3, 9).Dump();
        s.CombinationSum3(7, 28).Dump();
    }
}
