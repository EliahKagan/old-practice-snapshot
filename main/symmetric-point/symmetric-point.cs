using System;
using System.Collections.Generic;
using System.Linq;

internal static class Solution {
    private static T Next<T>(IEnumerator<T> en)
    {
        en.MoveNext();
        return en.Current;
    }

    private static IEnumerable<int> GetRecord(int fields)
    {
        return Console.ReadLine().Split().Select(int.Parse).Take(fields);
    }

    private static int Reflect(int focus, int point)
    {
        return focus * 2 - point;
    }

    private static void Main()
    {
        foreach (var t in Enumerable.Range(0, GetRecord(1).Single())) {
            int px, py, qx, qy;
            using (var en = GetRecord(4).GetEnumerator()) {
                px = Next(en);
                py = Next(en);
                qx = Next(en);
                qy = Next(en);
            }

            Console.WriteLine("{0} {1}", Reflect(qx, px), Reflect(qy, py));

        }
    }
}
