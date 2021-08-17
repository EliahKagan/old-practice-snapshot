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

public sealed class Frame {
    public Frame(int vertex) => Vertex = vertex;

    public int Vertex { get; }        // vertex we traverse from
    public int Pos { get; set; } = 0; // index into adj[vertex]
}

var vis = new bool[adj.Length];
var results = new Stack<int>(adj.Length);

void Dfs(int start) {
    if (vis[start]) return;

    vis[start] = true;
    var stack = new Stack<Frame>();
    stack.Push(new Frame(start));

    while (stack.Count != 0) {
        var frame = stack.Peek();

        if (frame.Pos == adj[frame.Vertex].Count) {
            stack.Pop();
            results.Push(frame.Vertex);
        } else {
            var neighbor = adj[frame.Vertex][frame.Pos++];
            if (vis[neighbor]) continue;

            vis[neighbor] = true;
            stack.Push(new Frame(neighbor));
        }
    }
}

for (var start = 0; start != adj.Length; ++start) Dfs(start);

while (results.Count != 0) Console.WriteLine(results.Pop());
