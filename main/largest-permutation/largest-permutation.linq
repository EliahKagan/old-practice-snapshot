<Query Kind="Program">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

private static int[] GetRecord(int count)
{
    var a = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
    Contract.Assert(a.Length == count);
    return a;
}

private static void Main()
{
    var nk = GetRecord(2);
    var n = nk[0];
    var k = nk[1];
    
    var values = GetRecord(n);
    var lookup = new int[n + 1];
    Action<int> track = i => lookup[values[i]] = i;
    for (var i = 0; i != n; ++i) track(i);
    
    Action<int, int> swap = (i, j) => {
        var tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
        
        track(i);
        track(j);
    };
    
    for (var i = 0; k != 0 && n != 0; ++i, --n) {
        if (values[i] == n) continue;
        swap(i, lookup[n]);
        --k;
    }
    
    Console.WriteLine(string.Join(" ", values));
}
