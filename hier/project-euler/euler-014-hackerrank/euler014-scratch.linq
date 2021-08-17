<Query Kind="Statements" />

const long max_seed = 5000000L;

var lengths = new int[max_seed + 1L];
lengths[1L] = 1;

for (var seed = 2L; seed <= max_seed; ++seed) {
    if (lengths[seed] != 0) continue;
    
    // trace chain to count hops
    var hops = 1;
    for (var i = seed; ; ++hops) {
        i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
        
        if (i <= max_seed && lengths[i] != 0) {
            hops += lengths[i];
            break;
        }
    }
    
    // retrace chain, marking lengths from hops count
    lengths[seed] = hops--;
    for (var i = seed; ; --hops) {
        i = (i % 2L == 0L ? i / 2L : i * 3L + 1L);
        
        if (i <= max_seed) {
            if (lengths[i] != 0) break;
            lengths[i] = hops;
        }
    }
}