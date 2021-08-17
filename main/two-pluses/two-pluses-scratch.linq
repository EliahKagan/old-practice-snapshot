<Query Kind="Program" />

private static bool // assumes (i1, i2) != (j1, j2)
AreDisjoint(int i1, int j1, int b1, int i2, int j2, int b2) // DEBUG only
{
    var di = Math.Abs(i1 - i2);
    var dj = Math.Abs(j1 - j2);
    
    var bsum = b1 + b2;
    if (di == 0) return dj > bsum;
    if (dj == 0) return di > bsum;
    
    return Math.Min(di, dj) > Math.Max(b1, b2);
}