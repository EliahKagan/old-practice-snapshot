'''Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.'''


'''
class Node:
    def __init__(self, val):
        self.right = None
        self.data = val
        self.left = None
'''

from collections import deque

# your task is to complete this function
# function should print the level order traversal of the binary tree in spiral order
# Note: You aren't required to print a new line after every test case
def printSpiralLevelOrder(root):
    if root is None:
        return

    path = []
    q = deque()
    q.append(root)

    while q:
        for _ in range(len(q)):
            root = q.pop()
            path.append(root.data)
            if root.right is not None:
                q.appendleft(root.right)
            if root.left is not None:
                q.appendleft(root.left)

        for _ in range(len(q)):
            root = q.popleft()
            path.append(root.data)
            if root.left is not None:
                q.append(root.left)
            if root.right is not None:
                q.append(root.right)

    print(*path, end='')
