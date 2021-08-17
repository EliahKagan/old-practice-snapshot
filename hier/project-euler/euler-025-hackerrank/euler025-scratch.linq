<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.Numerics.dll</Reference>
  <Namespace>System.Numerics</Namespace>
</Query>

internal static class Arith {
    internal static List<BigInteger> Fibonacci(this int n)
    {
        var seq = new List<BigInteger>(n + 1);
        seq.Add(BigInteger.Zero);
        seq.Add(BigInteger.One);
        
        var j = 1;
        for (var i = 0; i != n; ++i, ++j) seq.Add(seq[i] + seq[j]);
        
        return seq;
    }
    
    private static int RepresentationLength(BigInteger n)
            => n.ToString("R").Length;
            
    internal static int[] RepresentationLengthTable(this List<BigInteger> seq,
                                                    IEnumerable<int> indices)
    {
        var table = new int[seq.Count]; // we rely on "" representing no number
        
        foreach (var n in indices)
            if (table[n] == 0) table[n] = RepresentationLength(seq[n]);
        
        return table;
    }
}

internal static class Solution {
    private static int ReadValue() => int.Parse(Console.ReadLine());

    private static List<int> ReadAllValues()
    {
        var t = ReadValue();
        var a = new List<int>(t);
        while (t-- > 0) a.Add(ReadValue());
        return a;
    }
    
    private static void Main()
    {
        var values = ReadAllValues();
        //var table = values.
    }
}