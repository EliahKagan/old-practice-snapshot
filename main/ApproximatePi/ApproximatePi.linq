<Query Kind="Statements" />

double ApproximatePi(int digits)
{
    if (digits < 0) {
        throw new ArgumentOutOfRangeException(nameof(digits),
                $"{nameof(digits)} must be nonnegative");
    }

    IEnumerable<double> Guesses() // pi = 4(1 - 1/3 + 1/5 - 1/7 + ...)
    {
        var acc = 0.0;
        var sign = 1;
        
        for (var k = 0; ; ++k) {
            yield return acc; // an approximation in [0.0, 4.0]
            acc += 4.0 / (sign * (k * 2 + 1));
            sign *= -1;
        }
    }
    
    var cur = -1.0; // even early, coarse guesses won't round negative
    
    foreach (var guess in Guesses()) {
        var next = Math.Round(guess, digits, MidpointRounding.ToEven);
        if (cur == next) break;
        cur = next;
    }
    
    return cur;
}

for (var i = 0; i != 10; ++i) ApproximatePi(i).Dump();