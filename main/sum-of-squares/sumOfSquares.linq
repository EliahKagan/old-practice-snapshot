<Query Kind="Program" />

private static int SumOfSquares(int n)
        => Enumerable.Range(1, n).Sum(i => i * i);

private static void Main()
        => Console.WriteLine(SumOfSquares(100));