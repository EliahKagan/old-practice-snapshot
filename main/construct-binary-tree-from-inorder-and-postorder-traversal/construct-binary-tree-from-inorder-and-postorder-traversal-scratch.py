# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

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
            print('in_start = %d,  post_start = %d,  size = %d' % (in_start, post_start, size))
            
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

s = Solution()

# This test succeeds.

inorder1 = [1,6,13,9,14,4,7,33,23,34,18,24,15,25,19,26,10,16,27,20,28,3,5,29,21,30,17,31,22,32,11,8,12,0,2]
postorder1 = [13,14,9,6,33,34,23,24,18,25,26,19,15,27,28,20,16,10,7,4,29,30,21,31,32,22,17,11,12,8,5,3,1,2,0]
root1 = s.buildTree(inorder1, postorder1)
print(root1)

# This test fails because the the tree has duplicate values (which the problem statement prohibits).
inorder2 = [7,18,0,3,3,11,-44,51,12,-10,127,6,1,141,9,-23,14,56,7,19,-55,55,9,-1,100,22,14,66,83,-13,56,-2,82,2,4]
postorder2 = [0,3,3,18,51,-10,12,6,127,141,-23,9,1,7,-55,19,56,14,-44,11,-1,22,100,66,-13,83,14,56,82,-2,9,55,7,4,2]
root2 = s.buildTree(inorder2, postorder2)
print(root2)
