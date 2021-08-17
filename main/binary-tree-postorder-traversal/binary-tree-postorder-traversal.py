# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

from enum import Enum, unique

@unique
class Act(Enum):
    DISPLAY = 0
    GO_LEFT = 1
    GO_RIGHT = 2

class State(object):
    def __init__(self, node, act):
        self.node = node
        self.act = act

class Solution:
    def postorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        path = []
        if root is None:
            return path

        stack = [State(root, Act.GO_LEFT)]
        while stack:
            state = stack[-1]

            if state.act == Act.GO_LEFT:
                state.act = Act.GO_RIGHT
                left = state.node.left
                if left is not None:
                    stack.append(State(left, Act.GO_LEFT))
            elif state.act == Act.GO_RIGHT:
                state.act = Act.DISPLAY
                right = state.node.right
                if right is not None:
                    stack.append(State(right, Act.GO_LEFT))
            elif state.act == Act.DISPLAY:
                path.append(state.node.val)
                del stack[-1]
            else:
                raise ValueError('invalid state')

        return path
