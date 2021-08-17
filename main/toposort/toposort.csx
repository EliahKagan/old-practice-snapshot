// Adjacency list for a simple DAG that is not an arborescence.
var adj = Enumerable.Range(0, 7).Select(i => new List<int>()).ToArray();
adj[0].Add(1);
adj[1].Add(2);
adj[3].Add(2);
adj[5].Add(3);
adj[5].Add(4);
adj[6].Add(1);
adj[6].Add(3);
adj[6].Add(5);

var vis = new bool[adj.Length];
var results = new Stack<int>(adj.Length);

void Dfs(int src) {
    if (vis[src]) return;

    vis[src] = true;
    foreach (var dest in adj[src]) Dfs(dest);
    results.Push(src);
}

for (var start = 0; start != adj.Length; ++start) Dfs(start);

while (results.Count != 0) Console.WriteLine(results.Pop());
