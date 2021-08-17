<Query Kind="Program" />

// * Definition for a binary tree node.
public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
    
    public TreeNode(int x, TreeNode ln, TreeNode rn)
    {
        val = x;
        left = ln;
        right = rn;
    }
}

public class Solution {
    public IList<int> PreorderTraversal(TreeNode root) {
        var stack = new Stack<TreeNode>();
        var ret = new List<int>();
        
        while (root != null || stack.Count != 0) {
            for (; root != null; root = root.left) {
                ret.Add(root.val);
                stack.Push(root);
            }
            
            root = stack.Pop().right;
        }
        
        return ret;
    }
}

void Main()
{
    var s = new Solution();
    
    var r1 = new TreeNode(1, null, new TreeNode(2, new TreeNode(3), null));
    r1.Dump("tree");
    
    s.PreorderTraversal(r1).Dump("preorder traversal");
}
