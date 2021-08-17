using System;
using System.Linq;

internal static class Solution {
    private static int[] ReadPermutation()
    {
        Console.ReadLine(); // don't need n;
        
        return Enumerable.Concat(Enumerable.Repeat(0, 1),
                                 Console.ReadLine().Split().Select(int.Parse))
                         .ToArray();
    }
    
    private static int[] Inverse(this int[] permutation)
    {
        var inverse = new int[permutation.Length];
        
        for (var i = 0; i != permutation.Length; ++i)
            inverse[permutation[i]] = i;
        
        return inverse;
    }
    
    private static int[] Compose(this int[] first, int[] second)
            => first.Select(element => second[element]).ToArray();
    
    private static int[] SelfCompose(this int[] permutation)
            => permutation.Compose(permutation);
    
    private static void Main()
    {
        var permutation = ReadPermutation().Inverse().SelfCompose();
        
        foreach (var element in permutation.Skip(1))
            Console.WriteLine(element);
    }
}
