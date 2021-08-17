using System;

internal static class Solution {
    private static void Print(int[] arr, int size)
    {
        Console.Write(arr[0]);
        for (var i = 1; i < size; ++i) Console.Write(" {0}", arr[i]);
        Console.WriteLine();
    }

    private static void Main()
    {
        var size = int.Parse(Console.ReadLine());
        var arr = Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

        var i = size - 1;
        var e = arr[i];

        for (; 0 < i && e < arr[i - 1]; --i) {
            arr[i] = arr[i - 1];
            Print(arr, size);
        }

        arr[i] = e;
        Print(arr, size);
    }
}
