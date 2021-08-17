<Query Kind="Program" />

internal static class Program {
    private static int CountWays(int total, int[] coins) {
        var memo = new Dictionary<(int, int), int>();
        
        int Solve(int index, int subtot)
        {
            if (subtot == 0) return 1;
            if (index == coins.Length) return 0;
            //if (memo.TryGetValue((index, subtot), out var count)) return count;
            
            var coin = coins[index];
            if (coin <= 0) {
                throw new ArgumentException(
                        paramName: nameof(coins),
                        message: "coins must all have strictly positive values");
            }
            
            var count = 0;
            for (var next_subtot = subtot; next_subtot >= 0; next_subtot -= coin)
                count += Solve(index + 1, next_subtot);
            
            //memo.Add((index, subtot), count);
            return count;
        }
        
        return total < 0 ? 0 : Solve(0, total);
    }
    
    private static void Test(this int total, params int[] coins)
    {
        Console.WriteLine($"Total:  {total}");
        Console.WriteLine($"Coins:  {string.Join(", ", coins)}");
        Console.WriteLine($"Count:  {CountWays(total, coins)}");
        Console.WriteLine();
    }
    
    private static void Main()
    {
        49.Test(3, 2, 7);
        104.Test(3, 8, 2, 3, 9, 8, 5, 1, 14, 67, 108, 91, 19, 23, 1, 5);
    }
}
