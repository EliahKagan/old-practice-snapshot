using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private const int NoSolution = -1, Visited = 0, End = 100;
    
    private static int ReadValue() => int.Parse(Console.ReadLine());
    
    private static void ReadConnections(int[] board)
    {
        for (var n = ReadValue(); n > 0; --n) {
            var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            board[a[0]] = a[1];
        }
    }
    
    private static int[] ReadBoard()
    {
        var board = Enumerable.Range(0, End + 1).ToArray();
        
        ReadConnections(board); // ladders
        ReadConnections(board); // snakes
        
        return board;
    }
    
    private static int BreadthFirstSearch(this int[] board)
    {
        var q = new Queue<int>();
        q.Enqueue(1);
        board[1] = Visited;
        
        for (var turns = 1; q.Count != 0; ++turns) {
            for (var len = q.Count; len != 0; --len) {
                var i = q.Dequeue();
                
                for (var j = Math.Min(End, i + 6); j != i; --j) {
                    switch (board[j]) {
                    case Visited:
                        continue;
                        
                    case End:
                        return turns;
                        
                    default:
                        q.Enqueue(board[j]);
                        board[j] = Visited;
                        continue;
                    }
                }
            }
        }
        
        return NoSolution;
    }
    
    private static void Main()
    {
        for (var t = ReadValue(); t > 0; --t)
            Console.WriteLine(ReadBoard().BreadthFirstSearch());
    }
}
