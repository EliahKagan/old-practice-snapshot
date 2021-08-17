using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static int Encode(int r, int c) => r << 16 | c;
    
    private static bool Ok(this HashSet<int> ob, int r, int c)
            => !ob.Contains(Encode(r, c));
    
    private static void ReadPair(out int x, out int y)
    {
        var a = Console.ReadLine().Split();
        x = int.Parse(a[0]);
        y = int.Parse(a[1]);
    }
    
    private static void ReadCoords(out int r, out int c) // subtracts 1
    {
        ReadPair(out r, out c);
        --r;
        --c;
    }
    
    private static HashSet<int> ReadObstacles(int k)
    {
        var ob = new HashSet<int>();
        
        for (int r, c; k-- != 0; ob.Add(Encode(r, c)))
            ReadCoords(out r, out c);
        
        return ob;
    }
    
    private static HashSet<int> ReadBoard(out int n, out int rq, out int cq)
    {
        int k;
        ReadPair(out n, out k);
        ReadCoords(out rq, out cq);
        return ReadObstacles(k); // return value is obstacles set
    }
    
    private static void Main()
    {
        int n, rq, cq;
        var ob = ReadBoard(out n, out rq, out cq);
        var targs = 0;
        
        for (var c = cq; ++c != n && ob.Ok(rq, c); ) ++targs;   // east
        for (var c = cq; --c >= 0 && ob.Ok(rq, c); ) ++targs;   // west
        for (var r = rq; ++r != n && ob.Ok(r, cq); ) ++targs;   // south
        for (var r = rq; --r >= 0 && ob.Ok(r, cq); ) ++targs;   // north
        
        for (int c = cq, r = rq; ++c != n && ++r != n && ob.Ok(r, c); )
            ++targs;                                            // southeast
        for (int c = cq, r = rq; --c >= 0 && ++r != n && ob.Ok(r, c); )
            ++targs;                                            // southwest
        for (int c = cq, r = rq; ++c != n && --r >= 0 && ob.Ok(r, c); )
            ++targs;                                            // northeast
        for (int c = cq, r = rq; --c >= 0 && --r >= 0 && ob.Ok(r, c); )
            ++targs;                                            // northwest
        
        Console.WriteLine(targs);
    }
}
