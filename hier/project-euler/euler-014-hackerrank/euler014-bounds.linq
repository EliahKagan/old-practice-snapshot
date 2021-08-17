<Query Kind="Statements" />

const long min_seed = 1L, max_seed = 5000000L;

var s = new HashSet<long>();

checked {    
    for (var i = min_seed; i <= max_seed; ++i) {
        var k = i;
        while (!s.Contains(k)) {
            s.Add(k);
            k = (k % 2L == 0L ? k / 2L : k * 3L + 1L);
        }
    }
}

s.Count.Dump($"Count of values reached from seeds {min_seed}..{max_seed}:");
s.Max().Dump($"Highest value ever reached in chains from those seeds:");
s.Count(k => k <= max_seed).Dump("Count of values that were also seeds:");