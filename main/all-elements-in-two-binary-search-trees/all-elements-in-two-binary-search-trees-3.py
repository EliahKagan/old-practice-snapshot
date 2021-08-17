# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def getAllElements(self, root1: TreeNode, root2: TreeNode) -> List[int]:
        ret = inorder(root1)
        ret.extend(inorder(root2))
        ret.sort() # Timsort is very fast on input having long monotone runs.
        return ret

def inorder(root: TreeNode):
    out = []

    def dfs(node):
        if not node:
            return

        dfs(node.left)
        out.append(node.val)
        dfs(node.right)

    dfs(root)
    return out
