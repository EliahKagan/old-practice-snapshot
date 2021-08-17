<Query Kind="Program">
  <Namespace>System.Numerics</Namespace>
</Query>

internal static class Program {
    /// <summary>Helper class for <see cref="CountWays"/>.</summary>
    private sealed class ChangeMaker {
        internal ChangeMaker(int[] coins) =>_coins = coins;
        
        internal BigInteger Solve(int index, int subtot)
        {
            if (subtot == 0) return 1;
            if (index == _coins.Length) return 0;
            if (_memo.TryGetValue((index, subtot), out var count)) return count;
            
            var coin = _coins[index];
            if (coin <= 0) {
                throw new ArgumentException(
                        paramName: nameof(_coins),
                        message: "coins must all have strictly positive values");
            }
            
            count = 0;
            for (var next_subtot = subtot; next_subtot >= 0; next_subtot -= coin)
                count += Solve(index + 1, next_subtot);
            
            _memo.Add((index, subtot), count);
            return count;
        }
        
        private readonly int[] _coins;
        
        private readonly Dictionary<(int, int), BigInteger> _memo =
            new Dictionary<(int, int), BigInteger>();
    }
    
    private static BigInteger CountWays(int total, int[] coins)
        => total < 0 ? 0 : new ChangeMaker(coins).Solve(index: 0, subtot: total);
    
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
