<Query Kind="Statements" />

(int ans, long steps) MinimaxCost(int n)
{
    if (n <= 0) {
        throw new ArgumentOutOfRangeException(
                paramName: nameof(n),
                message: "n must be positive");
    }
    
    var table = new int[n + 2, n + 1];
    var steps = 0L; // for debugging
    
    for (var kstart = 2; kstart <= n; ++kstart) {
        var i = 1;
        for (var k = kstart; k <= n; ++i, ++k) {
            var min = int.MaxValue;
            
            for (var j = i; j <= k; ++j) {
                ++steps; // for debugging
                var cur = j + Math.Max(table[i, j - 1], table[j + 1, k]);
                if (min > cur) min = cur;
            }
            
            table[i, k] = min;
        }
    }
    
    return (table[1, n], steps);
}

for (var n = 1; n <= 1024; n *= 2) MinimaxCost(n).Dump($"{n}");