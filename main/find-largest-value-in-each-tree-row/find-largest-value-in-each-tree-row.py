# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

LOW = float('-inf')

class Solution:
    def largestValues(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        ret = []
        if root is None:
            return ret

        q = collections.deque()
        q.append(root)

        while q:
            acc = LOW

            for _ in range(len(q)):
                root = q.popleft()
                acc = max(acc, root.val)

                if root.left is not None:
                    q.append(root.left)
                if root.right is not None:
                    q.append(root.right)

            assert acc != LOW
            ret.append(acc)

        return ret
