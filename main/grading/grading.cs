using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int Get() => int.Parse(Console.ReadLine());
    
    private static IEnumerable<int> GetGrades()
            => Enumerable.Range(0, Get()).Select(_ => Get());
    
    private static int Round(int grade)
    {
        const int min_to_round = 38;
        const int grow = 5;
        const double shrink = (double)grow;
        
        if (grade < min_to_round) return grade;
        
        return Math.Max(grade, (int)Math.Round(grade / shrink) * grow);
    }
    
    private static void Main()
    {
        foreach (var rounded_grade in GetGrades().Select(Round))
            Console.WriteLine(rounded_grade);
    }
}
