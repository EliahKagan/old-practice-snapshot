<Query Kind="Program" />

public class Solution {
    private struct Candidate {
        internal Candidate(int value, int maxCount) {
            Value = value;
            MaxCount = maxCount;
        }
    
        internal readonly int Value, MaxCount;
    }

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

    private IList<IList<int>> CombinationSum2(Candidate[] candidates,
                                             int target) {
        // (index, subtot) => [ways...]
        var memo = new Dictionary<(int, int), List<Node>>();
        
        List<Node> Solve(int index, int subtot) {
            if (subtot == 0) return TrivialWay;
            if (index == candidates.Length) return NoWays;
            
            var key = (index, subtot);
            if (!memo.TryGetValue(key, out var ways)) {
                ways = new List<Node>();
                var can = candidates[index++];
                var count = 0;
                
                while (subtot >= 0 && count <= can.MaxCount) {
                    ways.AddRange(from tail in Solve(index, subtot)
                                  select new Node(can.Value, count, tail));
                    
                    ++count;
                    subtot -= can.Value;
                }
                
                memo.Add(key, ways);
            }
            
            return ways;
        }
        
        return Solve(0, target).ConvertAll(node => (IList<int>)node.ToArray());
    }

    public IList<IList<int>> CombinationSum2(int[] candidateValues,
                                             int target) {
        var freqs = new Dictionary<int, int>();
        
        foreach (var value in candidateValues) {
            freqs.TryGetValue(value, out var freq);
            freqs[value] = freq + 1;
        }
        
        var candidates = freqs.Select(kv => new Candidate(kv.Key, kv.Value))
                              .ToArray();
        Array.Sort(candidates, (lhs, rhs) => lhs.Value.CompareTo(rhs.Value));
        return CombinationSum2(candidates, target);
    }
}

internal static class UnitTest {
    private static void Main() {
        var s = new Solution();
        s.CombinationSum2(new[] { 10, 1, 2, 7, 6, 1, 5 }, 8).Dump();
        s.CombinationSum2(new[] { 2, 5, 3, 2, 2, 4, 4, 3, 5, 5 }, 20 ).Dump();
        s.CombinationSum2(new[] { 3, 4, 5, 2, 2, 3, 1, 1, 2, 1, 2, 2, 1, 2, 1, 3, 3, 1, 2, 2, 3, 2, 3, 5, 4, 4, 2, 3, 4, 2, 2, 3, 5, 1, 5, 4, 4, 2, 3, 4, 5, 5, 3, 3, 1, 4, 5, 4, 2, 3, 4, 2, 5, 5, 3, 5, 5, 1, 4, 3, 1, 5, 5, 4, 2, 1, 4, 2, 2, 5, 5, 1, 2, 2, 5, 1, 1, 5, 1, 5, 4, 2, 4, 5, 2, 1, 2, 5, 5, 1, 2, 2, 1, 3, 2, 5, 4, 3, 2, 3 }, 49).Count.Dump();
        //s.CombinationSum(new[] { 2, 3, 6, 7 }, 7).Dump();
        //s.CombinationSum(new[] { 1, 2, 3, 4, 5 }, 22).Dump();
    }
}