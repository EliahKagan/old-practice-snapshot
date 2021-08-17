#!/usr/bin/env python3

import collections

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def findFrequentTreeSum(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if root is None:
            return []

        freqs = collections.Counter()

        def dfs_sum(node):
            total = node.val
            if node.left is not None:
                total += dfs_sum(node.left)
            if node.right is not None:
                total += dfs_sum(node.right)
            freqs[total] += 1
            return total

        dfs_sum(root)
        max_freq = self._getMaxFreq(freqs)
        print(max_freq)
        return [total for total, freq in freqs.items() if freq == max_freq]

    def _getMaxFreq(self, freqs):
        print(freqs)
        return freqs.most_common(1)[0][1]

root = TreeNode(5)
root.left = TreeNode(2)
root.right = TreeNode(-3)
print(Solution().findFrequentTreeSum(root))
