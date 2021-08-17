<Query Kind="Program" />

private static int CountInversions(int[] a) // uses insertion sort
{
    var count = 0;
    
    for (var j = 0; j != a.Length; ++j) {
        var e = a[j];
        var i = j;
        for (; i != 0 && e < a[i - 1]; --i) a[i] = a[i - 1];
        a[i] = e;
        count += j - i;
    }
    
    return count;
}

private static int CountInversionsFast(int[] a) // uses mergesort
{
    var count = 0;
    var aux = new int[a.Length];

    Action<int, int, int> merge = (left, mid, right) => {
        var i = left;
        var j = mid +  1;
        var k = 0;

        while (i <= mid && j <= right) {
            if (a[i] <= a[j]) {
                aux[k++] = a[i++];
            } else {
                count += j - left - k;
                aux[k++] = a[j++];
            }
        }

        while (i <= mid) aux[k++] = a[i++];

        while (j <= right) aux[k++] = a[j++];

        Array.Copy(aux, 0, a, left, k);
    };

    Action<int, int> mergesort = null;
    mergesort = (left, right) => {
        if (left < right) {
            var mid = left + (right - left) / 2;
            mergesort(left, mid);
            mergesort(mid + 1, right);
            merge(left, mid, right);
        }
    };

    mergesort(0, a.Length - 1);
    return count;
}

private static void Test(params int[] a) 
{
    var b = (int[])a.Clone();
    CountInversions(a).Dump("slow");
    CountInversionsFast(b).Dump("fast");
    a.SequenceEqual(b).Dump("worked?");
}

private static void Main()
{
    Test(10, 30, 90, 40, 10, 20, 50, 80, 70, 60, 50);
    Test(1, 5, 2, 3, 9, 0, -6, -5, 1, -4, -14, 22, -21, -23, -45, 443, 0, 10, 0, -8, 3);
    Test(14, 12, 13, 18, 10, 5, 10, 5, 10, 5);
}
