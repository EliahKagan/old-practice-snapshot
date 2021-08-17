<Query Kind="Program" />

public class Solution {
    private sealed class Node {
        internal Node(int value, Node next) {
            Value = value;
            Next = next;
        }
        
        internal int[] ToArray(int length) {
            var ret = new int[length];
            var head = this;
            
            for (var i = 0; i != length; ++i) {
                ret[i] = head.Value;
                head = head.Next;
            }
            
            return ret;
        }
        
        private readonly int Value;
        private readonly Node Next;
    }
    
    // We are summing numbers in the range [Start, Stop).
    private const int Start = 1, Stop = 10;
    
    // These are common, reusable solutions for base cases. Don't modify them.
    private static readonly List<Node> NoWays = new List<Node> { };
    private static readonly List<Node> TrivialWay = new List<Node> { null };
    
    public IList<IList<int>> CombinationSum3(int k, int n) {
        // (len, 
        var memo = new Dictionary<(int, int), List<Node>>(); // (min,sum)=>ways
        
        List<Node> Solve(int min, int sum) {
            //if (sum < 0) return NoWays;
            //if (min == Stop) return sum == 0 ? TrivialWay : NoWays;
            
            var key = (min, sum);
            if (!memo.TryGetValue(key, out var ways)) {
                ways = new List<Node>();
                
            }
            
            return ways;
        }
        
        //return Solve(Start, n).ConvertAll(node => 
    }
}
