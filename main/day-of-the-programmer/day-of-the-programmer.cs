using System;

internal static class Solution {
    private static void WriteSpecialDate(int year, bool leapYear)
        => Console.WriteLine($"1{leapYear ? '2' : '3'}.09.{year}");
    
    private static void Main()
    {
        var y = int.Parse(Console.ReadLine());
        
        if (y < 1918) WriteSpecialDate(y, y % 4 == 0);
        else if (y == 1918) Console.WriteLine("26.09.1918");
        else WriteSpecialDate(y, y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));
        
    }
}
