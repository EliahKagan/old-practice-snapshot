# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def averageOfLevels(self, root):
        """
        :type root: TreeNode
        :rtype: List[float]
        """
        ret = []
        if root is None:
            return ret

        q = collections.deque()
        q.append(root)

        while q:
            row = []

            for _ in range(len(q)):
                root = q.popleft()
                row.append(root.val)
                if root.left is not None:
                    q.append(root.left)
                if root.right is not None:
                    q.append(root.right)

            ret.append(sum(row) / len(row))

        return ret
