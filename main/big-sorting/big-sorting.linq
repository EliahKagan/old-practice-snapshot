<Query Kind="Program" />

private static void Main()
{
    var n = int.Parse(Console.ReadLine());
    
    var a = Enumerable.Range(0, n)
                      .Select(_ => Console.ReadLine().Trim())
                      .ToArray();
    
    Array.Sort(a, Comparer<string>.Create((s, t) => {
        var len_delta = s.Length - t.Length;
        return len_delta == 0 ? string.CompareOrdinal(s, t) : len_delta;
    }));
    
    foreach (var w in a) Console.WriteLine(w);
}
