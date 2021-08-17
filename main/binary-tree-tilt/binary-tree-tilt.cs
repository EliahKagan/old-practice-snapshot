/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Solution {
    public int FindTilt(TreeNode root) {
        var acc = 0;
        
        int Traverse(TreeNode node) {
            if (node == null) return 0;
            
            var leftSum = Traverse(node.left);
            var rightSum = Traverse(node.right);
            acc += Math.Abs(leftSum - rightSum);
            return leftSum + rightSum + node.val;
        }
        
        Traverse(root);
        return acc;
    }
}
