<Query Kind="Program" />

private static void Main()
{
    var n = int.Parse(Console.ReadLine());

    var sorted = Enumerable.Range(0, n)
                           .Select(_ => Console.ReadLine().Trim())
                           .OrderBy(s => s.Length)
                           .ThenBy(s => s);

    foreach (var s in sorted) Console.WriteLine(s);
}
