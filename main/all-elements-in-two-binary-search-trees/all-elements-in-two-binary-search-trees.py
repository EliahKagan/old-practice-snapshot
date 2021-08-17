# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def getAllElements(self, root1: TreeNode, root2: TreeNode) -> List[int]:
        # Timsort is very fast when the input contains long monotone runs.
        return sorted(itertools.chain(inorder(root1), inorder(root2)))

def inorder(root: TreeNode):
    if not root:
        return
    yield from inorder(root.left)
    yield root.val
    yield from inorder(root.right)
