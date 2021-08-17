using System;

internal static class Solution {
    private static void print(int[] arr)
    {
        Console.Write(arr[0]);

        for (var i = 1; i < arr.Length; ++i)
            Console.Write(" {0}", arr[i]);

        Console.WriteLine();
    }

    static void insertionSort(int[] ar)
    {
        var i = ar.Length - 1;
        var e = ar[i];

        for (; 0 < i && e < ar[i - 1]; --i) {
            ar[i] = ar[i - 1];
            print(ar);
        }

        ar[i] = e;
        print(ar);
    }
    
    static void Main(String[] args)
    {
        int _ar_size;
        _ar_size = Convert.ToInt32(Console.ReadLine());
        int[] _ar = new int[_ar_size];
        String elements = Console.ReadLine();
        String[] split_elements = elements.Split(' ');
        for (int _ar_i = 0; _ar_i < _ar_size; _ar_i++) {
            _ar[_ar_i] = Convert.ToInt32(split_elements[_ar_i]);
        }

        insertionSort(_ar);
    }
}
