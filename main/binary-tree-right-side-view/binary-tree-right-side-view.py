# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def rightSideView(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        ret = []
        if root is None:
            return ret

        q = collections.deque((root,))
        while q:
            ret.append(q[-1].val)
            for _ in range(len(q)):
                root = q.popleft()
                if root.left is not None:
                    q.append(root.left)
                if root.right is not None:
                    q.append(root.right)

        return ret
