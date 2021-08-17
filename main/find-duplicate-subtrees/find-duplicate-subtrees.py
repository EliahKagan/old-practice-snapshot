class Solution:
    def findDuplicateSubtrees(self, root):
        """
        :type root: TreeNode
        :rtype: List[TreeNode]
        """
        serializations = collections.Counter() # serialization -> frequency
        dupes = [] # a representative subroot (we return these)

        def serialize(node):
            if node is None:
                return '()'

            s = '({}{}{})'.format(node.val, serialize(node.left),
                                            serialize(node.right))
            serializations[s] += 1
            if serializations[s] == 2:
                dupes.append(node)

            return s

        serialize(root)
        return dupes
