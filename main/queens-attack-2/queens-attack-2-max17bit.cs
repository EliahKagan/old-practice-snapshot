using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static long Encode(long r, long c) => r << 17 | c;
    
    private static bool Ok(this HashSet<long> ob, long r, long c)
            => !ob.Contains(Encode(r, c));
    
    private static void ReadPair(out long x, out long y)
    {
        var a = Console.ReadLine().Split();
        x = long.Parse(a[0]);
        y = long.Parse(a[1]);
    }
    
    private static void ReadCoords(out long r, out long c) // subtracts 1
    {
        ReadPair(out r, out c);
        --r;
        --c;
    }
    
    private static HashSet<long> ReadObstacles(long k)
    {
        var ob = new HashSet<long>();
        
        for (long r, c; k-- != 0; ob.Add(Encode(r, c)))
            ReadCoords(out r, out c);
        
        return ob;
    }
    
    private static HashSet<long> ReadBoard(out long n,
                                           out long rq, out long cq)
    {
        long k;
        ReadPair(out n, out k);
        ReadCoords(out rq, out cq);
        return ReadObstacles(k); // return value is obstacles set
    }
    
    private static void Main()
    {
        long n, rq, cq;
        var ob = ReadBoard(out n, out rq, out cq);
        var targs = 0;
        
        for (var c = cq; ++c != n && ob.Ok(rq, c); ) ++targs;   // east
        for (var c = cq; --c >= 0 && ob.Ok(rq, c); ) ++targs;   // west
        for (var r = rq; ++r != n && ob.Ok(r, cq); ) ++targs;   // south
        for (var r = rq; --r >= 0 && ob.Ok(r, cq); ) ++targs;   // north
        
        for (long c = cq, r = rq; ++c != n && ++r != n && ob.Ok(r, c); )
            ++targs;                                            // southeast
        for (long c = cq, r = rq; --c >= 0 && ++r != n && ob.Ok(r, c); )
            ++targs;                                            // southwest
        for (long c = cq, r = rq; ++c != n && --r >= 0 && ob.Ok(r, c); )
            ++targs;                                            // northeast
        for (long c = cq, r = rq; --c >= 0 && --r >= 0 && ob.Ok(r, c); )
            ++targs;                                            // northwest
        
        Console.WriteLine(targs);
    }
}
