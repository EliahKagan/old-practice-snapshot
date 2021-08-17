<Query Kind="Program" />

internal static class Algo {
    private static void Merge(this int[] a, int[] aux, int lo, int hi)
    {
        var mid = lo + (hi - lo) / 2;

        var i = lo;
        var j = mid + 1;
        var k = lo;

        while (i <= mid && j <= hi) // merge from left and right sides
            aux[k++] = (a[i] <= a[j] ? a[i++] : a[j++]);

        while (i <= mid) aux[k++] = a[i++]; // merge any remaining from left
        while (j <= hi)  aux[k++] = a[j++]; // ...or any remaining from right

        for (; lo != k; ++lo) a[lo] = aux[lo]; // copy back after merge
    }

    private static void Mergesort(this int[] a, int[] aux, int lo, int hi)
    {
        if (lo >= hi) return;

        var mid = lo + (hi - lo) / 2;
        a.Mergesort(aux, lo, mid);
        a.Mergesort(aux, mid + 1, hi);
        a.Merge(aux, lo, hi);
    }

    internal static void Mergesort(this int[] a)
        => a.Mergesort(new int[a.Length], 0, a.Length - 1);
}

internal static class UnitTest {
    private static void Main()
    {
        var r = new Random();
        var ok = true;
        
        for (var t = 1000; t != 0; --t) {
            var a = Enumerable.Range(0, r.Next(100))
                              .OrderBy(e => r.Next())
                              .ToArray();
            
            if (t % 100 == 0) a.Dump();

            a.Mergesort();
            var sorted = Enumerable.Range(0, a.Length).All(i => a[i] == i);
            Console.Write($"{(sorted ? "" : "FAIL:")}{a.Length} ");
            ok = ok && sorted;
        }

        Console.WriteLine(ok ? " Success." : " Fail.");
    }
}
