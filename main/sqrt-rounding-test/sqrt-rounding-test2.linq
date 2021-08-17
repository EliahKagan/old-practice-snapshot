<Query Kind="Program" />

internal static class UnitTest {
    private static void Main()
    {
        var wrong = 0;
        
        for (var i = 0u; i != uint.MaxValue; ++i) {
            if ((uint)Math.Sqrt(i) != Convert.ToUInt32(Math.Floor(Math.Sqrt(i)))) {
                i.Dump();
                ++wrong;
            }
        }
        
        wrong.Dump("Count of inaccurate computed roots:");
    }
}