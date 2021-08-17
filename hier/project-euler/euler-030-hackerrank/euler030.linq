<Query Kind="Program">
  <Namespace>static System.Console</Namespace>
  <Namespace>static System.Linq.Enumerable</Namespace>
</Query>

private static readonly long[,] lookup = { // lookup[n, d] = d**n
        { 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L, 1L },
        { 0L, 1L, 2L, 3L, 4L, 5L, 6L, 7L, 8L, 9L },
        { 0L, 1L, 4L, 9L, 16L, 25L, 36L, 49L, 64L, 81L },
        { 0L, 1L, 8L, 27L, 64L, 125L, 216L, 343L, 512L, 729L },
        { 0L, 1L, 16L, 81L, 256L, 625L, 1296L, 2401L, 4096L, 6561L },
        { 0L, 1L, 32L, 243L, 1024L, 3125L, 7776L, 16807L, 32768L, 59049L },
        { 0L, 1L, 64L, 729L, 4096L, 15625L, 46656L, 117649L, 262144L, 531441L }
};

private static long DigitPowerSum(int n, int k)
        => k.ToString().Sum(d => lookup[n, d - '0']);

private static void Main()
{
    const int b = 10, max = 1000000;
    
    var n = int.Parse(ReadLine());
    WriteLine(Range(b, max - b).Where(k => DigitPowerSum(n, k) == k).Sum());
}