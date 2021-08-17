<Query Kind="Program" />

internal static class Program {
    private static double Mean(this IList<int> values)
    {
        if (values is null)
            throw new ArgumentNullException(paramName: nameof(values));
        
        if (values.Count == 0) {
            throw new ArgumentException(
                        paramName: nameof(values),
                        message: "an empty sequence has no mean");
        }
        
        return values.Sum(Convert.ToInt64) / (double)values.Count;
    }
    
    private static double Mean(params int[] values) => values.Mean();
    
    private static void Main()
    {
        Mean(1, 2, 3, 4, 5, 6).Dump();
        
        Enumerable.Range(1, 6).ToList().Mean().Dump();
        
        try {
            Mean();
        } catch (ArgumentException e) {
            e.Message.Dump("Failure of legendary proportions");
        }
    }
}
