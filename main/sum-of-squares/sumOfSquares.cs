using System.Linq;

static class Program {
    static int SumOfSquares(int n) => Enumerable.Range(1, n).Sum(i => i * i);
    static void Main() => System.Console.WriteLine(SumOfSquares(100));
}
