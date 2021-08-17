const int range = 20;
const int divisor = 3;

int ComputeSumA()
{
    var acc = 0;

    foreach (var i in Enumerable.Range(1, range))
        if (i % divisor == 0) acc += i;
    
    return acc;
}

int ComputeSumB()
    => Enumerable.Range(1, range).Where(i => i % divisor == 0).Sum();

int ComputeSumC()
{
    var acc = 0;
    for (var i = divisor; i <= range; i += divisor) acc += i;
    return acc;
}

int ComputeSumD()
{
    const int scaled_input = range / divisor;
    const int scaled_output = (scaled_input * (scaled_input + 1) / 2);
    return scaled_output * divisor;
}

foreach (var f in new Func<int>[] {
        ComputeSumA, ComputeSumB, ComputeSumC, ComputeSumD}) {
    Console.WriteLine(f());
}
