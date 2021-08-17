using System;

internal static class Solution {
    private static int[] GetRecord()
            => Array.ConvertAll(Console.ReadLine().Split(' '), int.Parse);

    private static int ComputeEndgameEnergy(int[] c, int n, int k)
    {
        const int start_energy = 100, jump_cost = 1, thunder_penalty = 2;

        var e = start_energy;

        var i = 0;
        do {
            i = (i + k) % n;
            e -= jump_cost + c[i] * thunder_penalty;
        }
        while (i != 0);

        return e;
    }

    private static void Main()
    {
        var nk = GetRecord();
        Console.WriteLine(ComputeEndgameEnergy(GetRecord(), nk[0], nk[1]));
    }
}
