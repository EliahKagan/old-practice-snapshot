<Query Kind="Program" />

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
}

public class Solution {
    public int LongestUnivaluePath(TreeNode root) {
        var best = 0;
        
        int Dfs(TreeNode node) {
            if (node == null) return 0;
            
            var leftLen = Dfs(node.left);
            var rightLen = Dfs(node.right);
            
            var withLeft = (node.left?.val == node.val ? leftLen + 1 : 0);
            var withRight = (node.right?.val == node.val ? rightLen + 1 : 0);
            
            best = Math.Max(best, withLeft + withRight);
            return Math.Max(withLeft, withRight);
        }
        
        Dfs(root);
        return best;
    }
}

private static void Main() { }
