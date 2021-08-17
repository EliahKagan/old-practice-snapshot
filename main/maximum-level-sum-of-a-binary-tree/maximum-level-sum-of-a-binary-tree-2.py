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

        for cur_level, cur_sum in enumerate(level_sums(root), 1):
            if best_sum < cur_sum:
                best_sum = cur_sum
                best_level = cur_level

        return best_level


def level_sums(root):
    """Yields the sums of values in each level of a binary tree."""
    if not root:
        return

    queue = collections.deque((root,))

    while queue:
        acc = 0

        for _ in range(len(queue)):
            root = queue.popleft()
            acc += root.val

            if root.left:
                queue.append(root.left)
            if root.right:
                queue.append(root.right)

        yield acc
