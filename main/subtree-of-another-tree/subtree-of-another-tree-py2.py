# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def isSubtree(self, s, t):
        """
        :type s: TreeNode
        :type t: TreeNode
        :rtype: bool
        """
        table = collections.defaultdict(lambda: len(table))  # key -> id

        def key_from_subtree(node):
            return (node.val, id_from_key(node.left), id_from_key(node.right))

        def id_from_key(node):
            return -1 if node is None else table[key_from_subtree(node)]

        id_from_key(s)  # build table for the tree being searched
        return t is not None and key_from_subtree(t) in table
