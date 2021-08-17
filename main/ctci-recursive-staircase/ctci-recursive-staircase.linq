<Query Kind="Program" />

private static int Get() => int.Parse(Console.ReadLine());

// CountSums(max_total)[h] is the number of sequences whose elements
// are all 1, 2, or 3 and whose sum is h.
private static int[] CountSums(int max_total)
{
    var a = new int[max_total + 1];
    
    a[1] = 1; // (1)
    a[2] = 2; // (1, 1), (2)
    a[3] = 4; // (1, 1, 1), (2, 1), (1, 2), (3)
    
    for (var h = 4; h <= max_total; ++h)
        a[h] = checked(a[h - 1] + a[h - 2] + a[h - 3]);
    
    return a;
}

private static void Main()
{
    const int max_height = 36;
    var a = CountSums(max_height);
    for (var i = Get(); i > 0; --i) Console.WriteLine(a[Get()]);
}