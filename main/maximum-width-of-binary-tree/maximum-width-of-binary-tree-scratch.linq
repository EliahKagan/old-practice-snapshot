<Query Kind="Program" />

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
}

internal struct IndexedNode {
    public readonly int Index;
    public readonly TreeNode Node;
    
    public IndexedNode(int index, TreeNode node) {
        Index = index;
        Node = node;
    }
    
    public void Deconstruct(out int index, out TreeNode node) {
        index = Index;
        node = Node;
    }
}

public class Solution {
    private static void Swap<T>(ref T a, ref T b) {
        var tmp = a;
        a = b;
        b = tmp;
    }

    public int WidthOfBinaryTree(TreeNode root) {
        var acc = 0;
        if (root == null) return acc;
        
        var this_row = new List<IndexedNode> { new IndexedNode(1, root) };
        var next_row = new List<IndexedNode>();
        
        while (this_row.Count != 0) {
            acc = Math.Max(acc, this_row[this_row.Count - 1].Index
                                - this_row[0].Index + 1);
            
            foreach (var (index, node) in this_row) {
                if (node.left != null)
                    next_row.Add(new IndexedNode(index * 2, node.left));
                if (node.right != null)
                    next_row.Add(new IndexedNode(index * 2 + 1, node.right));
            }
            
            Swap(ref this_row, ref next_row);
            next_row.Clear();
        }
        
        return acc;
    }
}

private static void Main() { }
