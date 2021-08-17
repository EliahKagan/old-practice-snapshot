using System;

internal static class Solution {
    static void partition(int[] ar)
    {
        var n = ar.Length;

        var left = new int[n - 1];
        var right = new int[n - 1];
        var equal = new int[n];

        var nleft = 0;
        var nright = 0;
        var nequal = 1;

        var p = equal[0] = ar[0];

        for (var i = 1; i < n; ++i) {
            if (ar[i] < p)          left[nleft++] = ar[i];
            else if (ar[i] > p)     right[nright++] = ar[i];
            else                    equal[nequal++] = ar[i];
        }

        var sep = "";
        Action<int> write = i => {
            Console.Write("{0}{1}", sep, i);
            sep = " ";
        };

        for (var i = 0; i < nleft; ++i)   write(left[i]);
        for (var i = 0; i < nequal; ++i)  write(equal[i]);
        for (var i = 0; i < nright; ++i)  write(right[i]);
        Console.WriteLine();
    }

    private static void Main(String[] args)
    {
        int _ar_size;
        _ar_size = Convert.ToInt32(Console.ReadLine());
        int[] _ar = new int[_ar_size];
        String elements = Console.ReadLine();
        String[] split_elements = elements.Split(' ');
        for (int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
            _ar[_ar_i] = Convert.ToInt32(split_elements[_ar_i]);
        }

        partition(_ar);
    }
}
