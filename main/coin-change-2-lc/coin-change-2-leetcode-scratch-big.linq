<Query Kind="Program">
  <Namespace>System.Numerics</Namespace>
</Query>

internal static class Program {
    private static BigInteger CountWays(int total, int[] coins) {
        var memo = new Dictionary<(int, int), BigInteger>();
        
        BigInteger Solve(int index, int subtot)
        {
            if (subtot == 0) return 1;
            if (index == coins.Length) return 0;
            if (memo.TryGetValue((index, subtot), out var count)) return count;
            
            var coin = coins[index];
            if (coin <= 0) {
                throw new ArgumentException(
                        paramName: nameof(coins),
                        message: "coins must all have strictly positive values");
            }
            
            count = 0;
            for (var next_subtot = subtot; next_subtot >= 0; next_subtot -= coin)
                count += Solve(index + 1, next_subtot);
            
            memo.Add((index, subtot), count);
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
        1045.Test(3, 8, 2, 3, 9, 8, 5, 1, 14, 67, 108, 91, 19, 23, 1, 5);
        15_336.Test(15, 48, 2, 3, 1, 4, 8, 14, 13, 6, 5, 7, 9, 12, 10, 11, 202, 501, 63, 39, 29);
    }
}
