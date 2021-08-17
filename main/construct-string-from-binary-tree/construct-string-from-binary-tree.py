def serialize(root):
    if root.left is None:
        if root.right is None:
            return str(root.val)
        else:
            return '{}()({})'.format(root.val, serialize(root.right))
    else:
        if root.right is None:
            return '{}({})'.format(root.val, serialize(root.left))
        else:
            return '{}({})({})'.format(root.val, serialize(root.left),
                                                 serialize(root.right))

class Solution:
    def tree2str(self, t):
        """
        :type t: TreeNode
        :rtype: str
        """
        return '' if t is None else serialize(t)
