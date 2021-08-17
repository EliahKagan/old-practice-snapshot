<Query Kind="Statements" />

var a = new int[][] { new[] { 10, -3,  5 },
                      new[] { -4,  2, -1 },
                      new[] { -7,  9, 33 } };

a.SelectMany(x => x).Sum(x => Math.Min(0L, x)).GetType().Dump();
