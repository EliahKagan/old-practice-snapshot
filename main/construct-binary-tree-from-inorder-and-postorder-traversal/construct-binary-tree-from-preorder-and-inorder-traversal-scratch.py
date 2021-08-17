# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def buildTree(self, preorder, inorder):
        """
        :type preorder: List[int]
        :type inorder: List[int]
        :rtype: TreeNode
        """
        in_indices = {val: i for i, val in enumerate(inorder)}
        
        def build(size, pre_start, in_start):
            print('size=%d, pre_start=%d, in_start=%d' % (size, pre_start, in_start))
            
            if not size:
                return None
            
            assert size > 0
            
            val = preorder[pre_start]
            in_index = in_indices[val]
            assert in_start <= in_index < in_start + size
            
            left_size = in_index - in_start
            
            root = TreeNode(val)
            root.left = build(left_size, pre_start + 1, in_start)
            root.right = build(size - left_size - 1, pre_start + left_size + 1, in_index + 1)
            return root
        
        assert len(preorder) == len(inorder)
        return build(len(preorder), 0, 0)

s = Solution()

preorder0 = [3,9,20,15,7]
inorder0 = [9,3,15,20,7]
root0 = s.buildTree(preorder0, inorder0)
print(root0)

