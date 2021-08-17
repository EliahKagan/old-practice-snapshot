class Solution:
    def findDuplicateSubtrees(self, root):
        """
        :type root: TreeNode
        :rtype: List[TreeNode]
        """
        ids = {} # (val, left id #, right id #) -> id #
        nodes = [] # id # -> a representative subroot
        duped = [] # duped[i] is True iff id # i is duped

        def identify(node):
            if node is None:
                return -1

            key = node.val, identify(node.left), identify(node.right)
            try:
                i = ids[key]
                duped[i] = True # was found, so this dupes it
                return i
            except KeyError:
                i = len(nodes)
                ids[key] = i
                nodes.append(node)
                duped.append(False) # not yet duped
                return i

        identify(root)
        return [node for node, is_duped in zip(nodes, duped) if is_duped]
