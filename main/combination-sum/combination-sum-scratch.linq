<Query Kind="Program" />

public class Solution {
    private sealed class Node : IEnumerable<int> {
        internal Node(int value, int count, Node next = null) {
            Value = value;
            Count = count;
            Next = next;
        }
        
        public IEnumerator<int> GetEnumerator() {
            for (var head = this; head != null; head = head.Next) {
                for (var count = head.Count; count != 0; --count)
                    yield return head.Value;
            }
        }
        
        IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();
    
        internal readonly int Value, Count;
        internal readonly Node Next;
    }

    // These are common, reusable solutions for base cases. Don't modify them.
    private static readonly List<Node> NoWays = new List<Node> { };
    private static readonly List<Node> TrivialWay = new List<Node> { null };
    
    public IList<IList<int>> CombinationSum(int[] candidates, int target) {
        // (index, subtot) => [ways...]
        var memo = new Dictionary<(int, int), List<Node>>();
        
        List<Node> Solve(int index, int subtot) {
            if (subtot == 0) return TrivialWay;
            if (index == candidates.Length) return NoWays;
            
            var key = (index, subtot);
            if (!memo.TryGetValue(key, out var ways)) {
                ways = new List<Node>();
                var value = candidates[index++];
                var count = 0;
                
                for (; subtot >= 0; subtot -= value) {
                    ways.AddRange(from tail in Solve(index, subtot)
                                  select new Node(value, count, tail));
                    ++count;
                }
                
                memo.Add(key, ways);
            }
            
            return ways;
        }
        
        return Solve(0, target).ConvertAll(node => (IList<int>)node.ToArray());
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum(new[] { 2, 3, 6, 7 }, 7).Dump();
        s.CombinationSum(new[] { 1, 2, 3, 4, 5 }, 22).Dump();
    }
}
