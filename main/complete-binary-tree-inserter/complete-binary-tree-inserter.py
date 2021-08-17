# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class CBTInserter:
    def __init__(self, root):
        """
        :type root: TreeNode
        """
        self._root = root
        self._nodes = collections.deque((root,))
        
        while self._nodes[0].right is not None:
            root = self._nodes.popleft()
            self._nodes.append(root.left)
            self._nodes.append(root.right)
        
        if self._nodes[0].left is not None:
            self._nodes.append(self._nodes[0].left)

    def insert(self, v):
        """
        :type v: int
        :rtype: int
        """
        child = TreeNode(v)
        parent = self._nodes[0]
        
        if parent.left is None:
            parent.left = child
        else:
            parent.right = child
            del self._nodes[0]
        
        self._nodes.append(child)
        return parent.val

    def get_root(self):
        """
        :rtype: TreeNode
        """
        return self._root


# Your CBTInserter object will be instantiated and called as such:
# obj = CBTInserter(root)
# param_1 = obj.insert(v)
# param_2 = obj.get_root()
