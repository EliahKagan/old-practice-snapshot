<Query Kind="Program" />

// Doesn't work because (in LINQPad) Mul is implicitly nested in UserQuery,
// which is a non-static class. Gives CS1106 when compiled.
public static int[,] Mul(this int[,] self, int[,] other)
{
    if (self.GetLength(1) != other.GetLength(0)) {
        throw new ArgumentException(message:
                $"{self.GetLength(0)}-by-{self.GetLength(1)} can't multiply "
                    + $"{other.GetLength(0)}-by-{other.GetLength(1)}");
    }
    
    var ret = new int[self.GetLength(0), other.GetLength(1)];
    
    foreach (var i in Enumerable.Range(0, self.GetLength(0))) {
        foreach (var k in Enumerable.Range(0, other.GetLength(1))) {
            foreach (var j in Enumerable.Range(0, other.GetLength(0)))
                ret[i, k] += self[i, j] * other[j, k];
        }
    }
    
    return ret;
}

private static void Main() // unit test
{
    int[,] a = { { 1, 2 }, { 3, 4 } };
    int[,] b = { { 5, 6 }, { 7, 8 } };
    a.Mul(b).Dump();
}
