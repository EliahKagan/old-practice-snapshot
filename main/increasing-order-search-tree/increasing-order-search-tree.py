# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def increasingBST(self, root: TreeNode) -> TreeNode:
        head = TreeNode(None)
        link = head
        
        def dfs(subroot : TreeNode) -> None:
            nonlocal link
            
            while subroot is not None:
                dfs(subroot.left)
                subroot.left = None
                
                link.right = subroot
                link = link.right
                subroot = subroot.right
                link.right = None
        
        dfs(root)
        return head.right
