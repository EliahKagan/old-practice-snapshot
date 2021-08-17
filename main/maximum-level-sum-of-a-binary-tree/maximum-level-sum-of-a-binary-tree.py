# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def maxLevelSum(self, root: TreeNode) -> int:
        best_sum = -math.inf
        best_level = 0

        queue = collections.deque((root,))

        for cur_level in itertools.count(1):
            if not queue:
                break

            cur_sum = 0
            for _ in range(len(queue)):
                root = queue.popleft()
                cur_sum += root.val

                if root.left:
                    queue.append(root.left)
                if root.right:
                    queue.append(root.right)

            if best_sum < cur_sum:
                best_sum = cur_sum
                best_level = cur_level

        return best_level
