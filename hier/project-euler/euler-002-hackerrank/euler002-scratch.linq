<Query Kind="Statements" />

List<long> RunningSum(List<long> seq)
{
    var sums = new List<long>(seq.Count);

    var acc = 0L;
    foreach (var elem in seq) sums.Add(acc += elem);

    return sums;
}

List<long> EvenFibonacci(long max)
{
    for (var seq = new List<long> { 0L, 2L }; ; ) {
        var elem = seq[seq.Count - 2] + seq[seq.Count - 1] * 4;

        if (elem >= max) {
            if (elem == max) seq.Add(elem);
            return seq;
        }

        seq.Add(elem);
    }
}

var nmax = (long)Math.Pow(10, 16);
//EvenFibonacci(nmax).Dump();
RunningSum(EvenFibonacci(nmax)).Dump();