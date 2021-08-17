IndexedNode = collections.namedtuple('IndexedNode', ('index', 'node'))

class Solution:
    def widthOfBinaryTree(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        acc = 0
        if root is None:
            return acc

        this_row = [IndexedNode(1, root)]
        next_row = []

        while this_row:
            acc = max(acc, this_row[-1].index - this_row[0].index + 1)

            for index, node in this_row:
                if node.left is not None:
                    next_row.append(IndexedNode(index * 2, node.left))
                if node.right is not None:
                    next_row.append(IndexedNode(index * 2 + 1, node.right))

            this_row, next_row = next_row, this_row
            next_row.clear()

        return acc
