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
            
            if (node.val == node.left?.val) {
                if (node.val == node.right?.val) {
                    best = Math.Max(best, 1 + leftLen + rightLen);
                    return 1 + Math.Max(leftLen, rightLen);
                }
                
                var ret = 1 + leftLen;
                best = Math.Max(best, ret);
                return ret;
            }
            
            if (node.val == node.right?.val) {
                var ret = 1 + rightLen;
                best = Math.Max(best, ret);
                return ret;
            }
            
            best = Math.Max(best, 1);
            return 1;
        }
        
        Dfs(root);
        return best;
    }
}

private static void Main() { }
