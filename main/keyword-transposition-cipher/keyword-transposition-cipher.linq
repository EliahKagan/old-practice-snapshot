<Query Kind="Statements">
  <Namespace>System.Diagnostics.Contracts</Namespace>
</Query>

const int alen = 26;

var word = Console.ReadLine().Trim().ToUpperInvariant()
                             .Distinct().ToArray();
Contract.Assert(Array.TrueForAll(word, c => 'A' <= c && c <= 'Z'));

var n = word.Length;
Contract.Assert(n != 0, "can't use zero-length keyword");

var m = alen / n + Math.Sign(alen % n);
Contract.Assert((m - 1) * n < alen && alen <= m * n);

var grid = Array.ConvertAll(word, c => { // column-major representation
    var col = new char[m];
    col[0] = c;
    return col;
});

var k = n; // indexes grid in row-major order
foreach (var c in Enumerable.Range('A', alen).Select(Convert.ToChar)
                                             .Except(word)) {
    grid[k % n][k / n] = c;
    ++k;
}

Array.Sort(grid, (u, v) => u[0] - v[0]);
var cols = Array.ConvertAll(grid, col => new string(col).TrimEnd('\0'));
var key = string.Concat(cols);
Contract.Assert(key.Length == alen);

key.Dump();
