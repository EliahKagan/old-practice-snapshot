class Solution:
    def isSubtree(self, s, t):
        """
        :type s: TreeNode
        :type t: TreeNode
        :rtype: bool
        """
        ids = {}

        def create_ids(root):
            if root is None:
                return -1
            key = root.val, create_ids(root.left), create_ids(root.right)
            try:
                return ids[key]
            except KeyError:
                ids[key] = ret = len(ids)
                return ret

        def get_id(root):
            if root is None:
                return -1
            return ids[root.val, get_id(root.left), get_id(root.right)]

        create_ids(s)
        try:
            get_id(t)
            return True
        except KeyError:
            return False
