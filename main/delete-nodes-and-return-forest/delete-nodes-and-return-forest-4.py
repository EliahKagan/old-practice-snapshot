# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

import enum


class Solution:
    @staticmethod
    def delNodes(root: TreeNode, to_delete: List[int]) -> List[TreeNode]:
        """
        Removes nodes with the specified values.
        Returns a list roots of the resulting forest.
        """
        return forest_without(root, frozenset(to_delete))


@enum.unique
class Action(enum.Enum):
    """Phases of depth-first binary tree traversal."""
    GO_LEFT = enum.auto()
    GO_RIGHT = enum.auto()
    RETREAT = enum.auto()


class Frame:
    """A stack frame for iteratively implemented DFS on a binary tree."""

    __slots__ = ('_node', 'action')

    def __init__(self, node, action):
        """Creates a new frame with the given parent and current nodes."""
        self._node = node
        self.action = action

    @property
    def node(self):
        """Retrieves the node."""
        return self._node


def forest_without(root, vals):
    """Removes nodes with specified values. Lists the resulting roots."""
    roots = []
    stack = [Frame(root, Action.GO_LEFT)]
    last = None  # the node we just retreated from, if any

    while stack:
        frame = stack[-1]

        if frame.action is Action.GO_LEFT:
            if not frame.node:
                last = None
                del stack[-1]
                continue

            stack.append(Frame(frame.node.left, Action.GO_LEFT))
            frame.action = Action.GO_RIGHT
        elif frame.action is Action.GO_RIGHT:
            frame.node.left = last
            stack.append(Frame(frame.node.right, Action.GO_LEFT))
            frame.action = Action.RETREAT
        else:
            assert frame.action is Action.RETREAT, 'unrecognized action'
            frame.node.right = last

            if frame.node.val in vals:
                if frame.node.left:
                    roots.append(frame.node.left)
                if frame.node.right:
                    roots.append(frame.node.right)
                last = None
            else:
                last = frame.node

            del stack[-1]

    if last:
        roots.append(last)
    return roots
