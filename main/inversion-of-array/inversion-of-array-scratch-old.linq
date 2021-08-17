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
    var aux = new int[a.Length];
    
    void Merge(int left, int mid, int right) {
        var i = left;
        var j = mid + 1;
        var k = 0;
        
        while (i <= mid && j <= right)
            aux[k++] = (a[i] <= a[j] ? a[i++]  : a[j++]);
        
        while (i <= mid) aux[k++] = a[i++];
        
        while (j <= right) aux[k++] = a[j++];
        
        Array.Copy(aux, 0, a, left, k);
    }
    
    void Mergesort(int left, int right) {
        if (left < right) {
            var mid = left + (right - left) / 2;
            Mergesort(left, mid);
            Mergesort(mid + 1, right);
            Merge(left, mid, right);
        }
    }
    
    Mergesort(0, a.Length - 1);
    return 0; // FIXME: instrument the mergesort to count "inversions" and return
}

private static void Main()
{
    var a = new int[] { 10, 30, 90, 40, 10, 20, 50, 80, 70, 60, 50 };
    CountInversionsFast(a).Dump();
    a.Dump();
}
