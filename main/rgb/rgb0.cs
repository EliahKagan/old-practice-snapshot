// rgb0.cs - simple function to format 3 bytes as RGB value, with unit test

using System;

internal static class Program {
    private static string RGBFormat(byte r, byte g, byte b)
    {
        return string.Format("{0:X2}{1:X2}{2:X2}", r, g, b);
    }

    private static void Main()
    {
        Console.WriteLine(RGBFormat(10, 20, 30));
    }
}
