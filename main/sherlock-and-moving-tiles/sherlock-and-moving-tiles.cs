using System;
using static System.Math;

internal static class Solution {
    private static void Main()
    {
        var general_params = Array.ConvertAll(Console.ReadLine().Split(' '),
                                              double.Parse);
        var length = general_params[0];
        var relative_speed = Abs(general_params[1] - general_params[2]);
        var sqrt2 = Sqrt(2.0);

        for (var query = int.Parse(Console.ReadLine()); query > 0; --query) {
            var overlap_area = double.Parse(Console.ReadLine());
            var time = (length - Sqrt(overlap_area)) * sqrt2 / relative_speed;
            Console.WriteLine("{0:0.0000######}", time);
        }
    }
}
