<Query Kind="Program" />

private static int ComputeSignature(int?[] a) // note: destroys data in a
{
    var sig = 1;

    for (var i = 1;  (i = Array.FindIndex(a, i, k => k.HasValue)) >= 0; ) {
        var len = 0; // easier to debug a per-cycle length than a signature

        int? current = i;
        do {
            ++len;
            var next = a[current.Value];
            a[current.Value] = null;
            current = next;
        }
        while (current.HasValue);

        if (len % 2 != 0) sig *= -1;
    }

    return sig;
}

private static void Main()
{
    int?[] a = { null, 2, 1, 3, 4 };
    ComputeSignature(a).Dump();
}