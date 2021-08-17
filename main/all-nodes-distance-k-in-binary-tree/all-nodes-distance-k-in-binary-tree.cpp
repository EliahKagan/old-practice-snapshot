# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    @staticmethod
    def distanceK(root, target, K):
        """
        :type root: TreeNode
        :type target: TreeNode
        :type K: int
        :rtype: List[int]
        """
        adj = Solution.buildAdjacencyList(root)
        return list(Solution.findBreadth(adj, target.val, K))
    
    @staticmethod
    def findBreadth(adj, start, depth):
        vis = {start}
        queue = collections.deque((start,))
        
        for _ in range(depth):
            if not queue:
                break
            
            for _ in range(len(queue)):
                cur = queue.popleft()
                
                for nei in adj[cur]:
                    if nei not in vis:
                        vis.add(nei)
                        queue.append(nei)
        
        return queue
    
    @staticmethod
    def buildAdjacencyList(root):
        adj = collections.defaultdict(set)
        
        stack = [root]
        while stack:
            parent = stack.pop()
            
            for child in parent.left, parent.right:
                if child is not None:
                    adj[parent.val].add(child.val)
                    adj[child.val].add(parent.val)
                    stack.append(child)
        
        return adj
