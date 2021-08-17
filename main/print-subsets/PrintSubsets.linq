<Query Kind="Program" />

internal static class Program {
    private static void PrintSubsets(IList items)
    {
        var len = checked(1 << items.Count);
        
        for (var i = 0; i != len; ++i) {
            var mask = i;
            foreach (var x in items) {
                if ((mask & 1) != 0) Console.Write($"{x}, ");
                mask >>= 1;
            }
            
            Console.WriteLine();
        }
    }
    
    private static void PrintSubsets(params object[] items)
        => PrintSubsets((IList)items);
    
    private static void Main()
    {
        PrintSubsets();
        PrintSubsets("foo", "bar", "baz");
        PrintSubsets(1, 2, 3, 4);
        PrintSubsets(1, 2, 3, 4, 5);
    }
}
