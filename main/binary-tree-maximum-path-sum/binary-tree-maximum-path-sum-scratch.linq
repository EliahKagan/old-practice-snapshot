<Query Kind="Program" />

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int x) { val = x; }
}

public class Solution {
    public int MaxPathSum(TreeNode root) {
        var max = int.MinValue;
        
        int Dfs(TreeNode node) {
            if (node == null) return 0;
            
            var leftSum = Dfs(node.left);
            var rightSum = Dfs(node.right);
            var ret = node.val + Math.Max(0, Math.Max(leftSum, rightSum));
            
            max = Math.Max(max, Math.Max(ret, node.val + leftSum + rightSum));
            return ret;
        }
        
        Dfs(root);
        return max;
    }
}

private static void Main() {
    var s = new Solution();

    var root = new TreeNode(1);
    root.left = new TreeNode(2);
    
    s.MaxPathSum(root).Dump();
}
