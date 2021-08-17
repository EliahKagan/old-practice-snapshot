// rgb.cs - interpret 3 bytes as RGB (or similar), formatting in hexadecimal
//     If that is really all the functionality that will be needed, consider
//     using the implementation in rgb0.cs, which is significantly simpler.

using System;
using System.Text;

[assembly:System.Reflection.AssemblyVersion("0.2.0.0")]

internal static class Program {
    private static string BytesToHexString(params byte[] values)
    {
        var capacity = values.Length * 2;
        if (capacity == 0) return "";

        var sb = new StringBuilder(capacity, capacity);
        foreach (var k in values) sb.AppendFormat("{0:X2}", k);
        return sb.ToString();
    }

    private static string RGBFormat(byte r, byte g, byte b)
        // Trivial wrapper for BytesToHexString(), providing compile-time
        // validation that it is called with the correct number of byte
        // arguments (and that they are not passed as an array).
    {
        return BytesToHexString(r, g, b);
    }

    private static void Main()
    {
        Console.WriteLine(RGBFormat(10, 20, 30));
    }
}
