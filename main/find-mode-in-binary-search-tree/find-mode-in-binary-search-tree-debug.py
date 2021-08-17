# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def findMode(root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        modes = []
        
        if root is None:
            return modes
        
        max_freq = freq = 0
        prev = None
        
        for cur in itertools.chain(Solution._dfs(root), (None,)):
            print(cur) # FIXME: remove after debugging
            
            if prev == cur:
                freq += 1
                continue
            
            print('max_freq', max_freq, 'freq', freq) # FIXME: remove after debugging
            
            if max_freq <= freq:
                if max_freq != freq:
                    max_freq = freq
                    modes.clear()
                    
                print('Appending', prev)
                modes.append(prev)
            
            freq = 1
            prev = cur
        
        return modes
    
    @staticmethod
    def _dfs(root):
        if root is not None:
            yield from Solution._dfs(root.left)
            yield root.val
            yield from Solution._dfs(root.right)
