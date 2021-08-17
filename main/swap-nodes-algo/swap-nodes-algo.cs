using System;
using System.Collections.Generic;
using System.Linq;

[assembly: System.Reflection.AssemblyVersion("1.0.0.0")]

internal static class Util {
    internal static int ReadVal() => int.Parse(Console.ReadLine());

    internal static void Swap<T>(ref T x, ref T y)
    {
        var tmp = x;
        x = y;
        y = tmp;
    }
}

internal sealed class Node {
    public readonly int Id;
    public Node Left, Right;

    public Node(int id, Node left = null, Node right = null)
    {
        Id = id;
        Left = left;
        Right = right;
    }
}

internal static class Tree {
    private static IEnumerable<Node> CreateUnconnectedNodes(int n)
        => from i in Enumerable.Range(1, n) select new Node(i);

    private static Node[] CreateUnconnectedNodesAsArray(int n)
        => Enumerable.Repeat((Node)null, 1)
                     .Concat(CreateUnconnectedNodes(n))
                     .ToArray();

    internal static Node ReadTree()
    {
        const int no_node = -1;

        var a = CreateUnconnectedNodesAsArray(Util.ReadVal());

        for (var i = 1; i != a.Length; ++i) {
            var lr = Array.ConvertAll(Console.ReadLine().Split(), int.Parse);
            if (lr[0] != no_node) a[i].Left = a[lr[0]];
            if (lr[1] != no_node) a[i].Right = a[lr[1]];
        }

        return a[1];
    }

    internal static IEnumerable<int> InOrder(this Node root)
    {
        if (root != null) {
            foreach (var id in root.Left.InOrder()) yield return id;
            yield return root.Id;
            foreach (var id in root.Right.InOrder()) yield return id;
        }
    }

    internal static void SwapNodes(this Node root, int k, int h = 1)
    {
        if (root != null) {
            if (h == k) {
                Util.Swap(ref root.Left, ref root.Right);
                root.Left.SwapNodes(k);
                root.Right.SwapNodes(k);
            } else {
                root.Left.SwapNodes(k, h + 1);
                root.Right.SwapNodes(k, h + 1);
            }
        }
    }
}

internal static class Solution {
    private static void Main()
    {
        var root = Tree.ReadTree();

        for (var t = Util.ReadVal(); t > 0; --t) {
            root.SwapNodes(Util.ReadVal());
            Console.WriteLine(string.Join(" ", root.InOrder()));
        }
    }
}
