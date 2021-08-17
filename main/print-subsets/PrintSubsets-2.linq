<Query Kind="Program" />

internal static class Program {
    private static void PrintSubsets(this TextWriter writer, IList items)
    {
        var len = checked(1 << items.Count);
        
        for (var i = 0; i != len; ++i) {
            var mask = i;
            foreach (var x in items) {
                if ((mask & 1) != 0) writer.Write($"{x}, ");
                mask >>= 1;
                if (mask == 0) break;
            }
            
            writer.WriteLine();
        }
    }
    
    private static void PrintSubsets(this TextWriter writer,
                                     IEnumerable items)
        => writer.PrintSubsets(items.Cast<object>().ToList());
    
    private static void PrintSubsets(this TextWriter writer,
                                     params object[] items)
        => writer.PrintSubsets((IList)items);
    
    private static void Main()
    {
        Console.Out.PrintSubsets();
        Console.Out.PrintSubsets("foo", "bar", "baz");
        Console.Out.PrintSubsets(1, 2, 3, 4);
        Console.Out.PrintSubsets(Enumerable.Range(0, 5));
        
        TextWriter.Null.PrintSubsets(Enumerable.Range(0, 5));
        TextWriter.Null.PrintSubsets(Enumerable.Range(0, 24));
    }
}
