# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def buildTree(self, inorder, postorder):
        """
        :type inorder: List[int]
        :type postorder: List[int]
        :rtype: TreeNode
        """
        assert len(inorder) == len(postorder)
        in_indices = {val: index for index, val in enumerate(inorder)}
        
        def dfs(in_start, post_start, size):
            if size == 0:
                return None
            
            assert size > 0
            
            val = postorder[post_start + size - 1]
            in_index = in_indices[val]
            assert in_start <= in_index < in_start + size
            delta = in_index - in_start
            
            root = TreeNode(val)
            root.left = dfs(in_start, post_start, delta)
            root.right = dfs(in_index + 1, post_start + delta, size - delta - 1)
            return root
        
        return dfs(0, 0, len(inorder))
