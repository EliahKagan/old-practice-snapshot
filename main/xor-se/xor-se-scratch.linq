<Query Kind="Statements" />

const int n = 100;

var a = new int[n];
for (var k = 1; k != n; ++k) a[k] = a[k - 1] ^ k;

var b = new int?[n, n];
for (var i = 0; i != n; ++i) {
    for (var j = i; j != n; ++j) {
        var elem = 0;
        for (var k = i; k <= j; ++k) elem ^= a[k];
        b[i, j] = elem;
    }
}

b.Dump();