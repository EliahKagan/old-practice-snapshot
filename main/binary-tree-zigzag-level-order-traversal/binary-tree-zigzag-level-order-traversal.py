# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def zigzagLevelOrder(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
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
            ret.append(row)

            if not q:
                break

            row = []
            for _ in range(len(q)):
                root = q.pop()
                row.append(root.val)
                if root.right is not None:
                    q.appendleft(root.right)
                if root.left is not None:
                    q.appendleft(root.left)
            ret.append(row)

        return ret
