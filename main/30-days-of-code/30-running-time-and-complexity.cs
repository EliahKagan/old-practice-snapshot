using static System.Console;
using static System.Math;

internal static class Solution {
    private static bool IsPrime(int n)
    {
        if (n < 2) return false;
    
        var r = System.Convert.ToInt32(Floor(Sqrt(n)));
    
        for (var i = 2; i <= r; ++i)
            if (n % i == 0) return false;
    
        return true;
    }

    private static int Get() => int.Parse(ReadLine());

    private static void Main()
    {
        for (var t = Get(); t > 0; --t)
            WriteLine(IsPrime(Get()) ? "Prime" : "Not prime");
    }
}
